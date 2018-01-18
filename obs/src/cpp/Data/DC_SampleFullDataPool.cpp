  
//
// Copyright 2003 P&P Software GmbH - All Rights Reserved
//
// DC_SampleFullDataPool.cpp
//
// Automatically generated file

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../Base/CC_RootObject.h"
#include "../System/ObsClock.h"
#include "../Data/DC_SettableDataItem.h"
#include "DC_SampleFullDataPool.h"

static unsigned int const TD_FloatCode = 1;
static unsigned int const TD_IntegerCode = 2;

DC_SampleFullDataPool::DC_SampleFullDataPool(void) {
   setClassId(ID_SAMPLEFULLDATAPOOL);

   pDefaultFloat = new TD_Float();
   *pDefaultFloat = (TD_Float)0;
   pDefaultInt = new TD_Integer();
   *pDefaultInt = (TD_Integer)0;

   iterationCounter = 0;
   unsigned int const numberOfRealPar = 4;
   unsigned int const numberOfIntPar = 4;
   size = numberOfRealPar*sizeof(TD_Float)+numberOfIntPar*sizeof(TD_Integer);
   maxParId = 11;
   value = (unsigned char*)(new double[(size/sizeof(double))+1]);
   pValue = new unsigned char*[maxParId+1];         
   backUpValue = new unsigned char[size];
   pBackUpValue = new unsigned char*[maxParId+1]; 
   pObsClock = pNULL;
   timeStamp = new TD_ObsTime[maxParId+1];
   valid = new bool[maxParId+1];   
   pDataItem = new DC_SettableDataItem*[maxParId+1];    
   pMonitoringProfile = new MonitoringProfile*[maxParId+1];       
   pRecoveryAction = new RecoveryAction*[maxParId+1];       
   type = new char[maxParId+1];                 

   for (TD_DataPoolId i=0; i<size; i++)  {
        value[i] = 0;  
        backUpValue[i] = 0;          
   }

   for (TD_DataPoolId i=0; i<=maxParId; i++)  {
        pValue[i] = pNULL;         
        pBackUpValue[i] = pNULL;          
        timeStamp[i] = 0;               
        valid[i] = true;                
        pDataItem[i] = pNULL;   
        pMonitoringProfile[i] = pNULL;          
        pRecoveryAction[i] = pNULL;             
        type[i] = -1;                           
   }

 unsigned int offset = 0;           
 type[1] = TD_IntegerCode;  
 type[2] = TD_FloatCode;  
 type[4] = TD_IntegerCode;  
 type[5] = TD_FloatCode;  
 type[7] = TD_IntegerCode;  
 type[8] = TD_FloatCode;  
 type[10] = TD_IntegerCode;  
 type[11] = TD_FloatCode;  
 // Store the TD_Float values in the first part of the array
 for (TD_DatabaseId i=0; i<=maxParId; i++)  {
     if (type[i]==TD_FloatCode) {
        pValue[i] = value + offset;                                  
        pBackUpValue[i] = backUpValue + offset;         
        pDataItem[i] = new DC_SettableDataItem((TD_Float*)pValue[i]);     
        offset = offset + sizeof(TD_Float);                     
     } 
 }

 // Now ensure that offset is aligned with a TD_Integer
 unsigned int temp = (offset/sizeof(TD_Integer));
 if (temp*sizeof(TD_Integer)<offset)
    offset = (temp+1)*sizeof(TD_Integer);

 // Store the TD_Integer values in the second part of the array
 for (TD_DatabaseId i=0; i<=maxParId; i++)  {
     if (type[i]==TD_IntegerCode) {
        pValue[i] = value + offset;                                  
        pBackUpValue[i] = backUpValue + offset;         
        pDataItem[i] = new DC_SettableDataItem((TD_Integer*)pValue[i]);     
        offset = offset + sizeof(TD_Integer);                     
     } 
 }
       

}

 
void DC_SampleFullDataPool::setObsClock(ObsClock* pObsClock) {
    assert( pObsClock != pNULL );               
    this->pObsClock = pObsClock;
}

ObsClock* DC_SampleFullDataPool::getObsClock(void) const {
    return pObsClock;
}
 

void DC_SampleFullDataPool::setValue(TD_DataPoolId id, TD_Float newValue) {
    assert( id <= maxParId );               
    assert( type[id] == TD_FloatCode );
 
    if ( id > maxParId ) {
        CC_RootObject::getEventRepository()->create(this,EVT_ILLEGAL_DP_ACCESS);
        return;
    }
    if ( type[id] != TD_FloatCode ) {
        CC_RootObject::getEventRepository()->create(this,EVT_ILLEGAL_DP_ACCESS);
        return;
    }
    (*(TD_Float*)pValue[id]) = newValue;        
    timeStamp[id] = pObsClock->getTime();        
    if ( valid[id] )
        (*(TD_Float*)pBackUpValue[id]) = newValue;          
}

void DC_SampleFullDataPool::setValue(TD_DataPoolId id, TD_Integer newValue) {
    assert( id <= maxParId );           
    assert( type[id] == TD_IntegerCode );
 
    if ( id > maxParId ) {
        CC_RootObject::getEventRepository()->create(this,EVT_ILLEGAL_DP_ACCESS);
        return;
    }
    if ( type[id] != TD_IntegerCode ) {
        CC_RootObject::getEventRepository()->create(this,EVT_ILLEGAL_DP_ACCESS);
        return;
    }
    (*(TD_Integer*)pValue[id]) = newValue;      
    timeStamp[id] = pObsClock->getTime();        
    if ( valid[id] )
        (*(TD_Integer*)pBackUpValue[id]) = newValue;        
}

TD_Float DC_SampleFullDataPool::getFloatValue(TD_DataPoolId id) {
    assert( id <= maxParId );           
    assert( type[id] == TD_FloatCode );
 
    if ( id > maxParId ) {
        CC_RootObject::getEventRepository()->create(this,EVT_ILLEGAL_DP_ACCESS);
        return (TD_Float)0;
    }
    if ( type[id] != TD_FloatCode ) {
        CC_RootObject::getEventRepository()->create(this,EVT_ILLEGAL_DP_ACCESS);
        return (TD_Float)0;
    }
    if ( valid[id] )
        return (*(TD_Float*)pValue[id]);
    else
        return (*(TD_Float*)pBackUpValue[id]);
   
}

TD_Integer DC_SampleFullDataPool::getIntegerValue(TD_DataPoolId id) {
    assert( id <= maxParId );           
    assert( type[id] == TD_IntegerCode );
 
    if ( id > maxParId ) {
        CC_RootObject::getEventRepository()->create(this,EVT_ILLEGAL_DP_ACCESS);
        return (TD_Integer)0;
    }
    if ( type[id] != TD_IntegerCode ) {
        CC_RootObject::getEventRepository()->create(this,EVT_ILLEGAL_DP_ACCESS);
        return (TD_Integer)0;
    }
    if ( valid[id] )
        return (*(TD_Integer*)pValue[id]);
    else
        return (*(TD_Integer*)pBackUpValue[id]);
   
}

TD_Float* DC_SampleFullDataPool::getPointerFloatValue(TD_DataPoolId id) {
    assert( id <= maxParId );           
    assert( type[id] == TD_FloatCode );
 
    if ( id > maxParId ) {
        CC_RootObject::getEventRepository()->create(this,EVT_ILLEGAL_DP_ACCESS);
        return pDefaultFloat;
    }
    if ( type[id] != TD_FloatCode ) {
        CC_RootObject::getEventRepository()->create(this,EVT_ILLEGAL_DP_ACCESS);
        return pDefaultFloat;
     }
    return ((TD_Float*)pValue[id]);
}

TD_Integer* DC_SampleFullDataPool::getPointerIntegerValue(TD_DataPoolId id) {
    assert( id <= maxParId );           
    assert( type[id] == TD_IntegerCode );
 
    if ( id > maxParId ) {
        CC_RootObject::getEventRepository()->create(this,EVT_ILLEGAL_DP_ACCESS);
        return pDefaultInt;
    }
    if ( type[id] != TD_IntegerCode ) {
        CC_RootObject::getEventRepository()->create(this,EVT_ILLEGAL_DP_ACCESS);
        return pDefaultInt;
    }
    return ((TD_Integer*)pValue[id]);
}

 
DC_DataItem* DC_SampleFullDataPool::getDataItem(TD_DataPoolId id) {
    assert( id <= maxParId );           
    assert( type[id] != -1 );
 
    if ( id > maxParId ) {
        CC_RootObject::getEventRepository()->create(this,EVT_ILLEGAL_DP_ACCESS);
        return DataPool::getDataItem(id);
    }
    if ( type[id] == -1 ) {
        CC_RootObject::getEventRepository()->create(this,EVT_ILLEGAL_DP_ACCESS);
        return DataPool::getDataItem(id);
    }
    return pDataItem[id];
}
 
TD_ObsTime DC_SampleFullDataPool::getTimeStamp(TD_DataPoolId id) {
    assert( id <= maxParId );           
    assert( type[id] != -1 );
 
    if ( id > maxParId ) {
        CC_RootObject::getEventRepository()->create(this,EVT_ILLEGAL_DP_ACCESS);
        return DataPool::getTimeStamp(id);
    }
    if ( type[id] == -1 ) {
        CC_RootObject::getEventRepository()->create(this,EVT_ILLEGAL_DP_ACCESS);
        return DataPool::getTimeStamp(id);
    }
    return timeStamp[id];
}
 
bool DC_SampleFullDataPool::isValid(TD_DataPoolId id) {
    assert( id <= maxParId );               
    assert( type[id] != -1 );
 
    if ( id > maxParId ) {
        CC_RootObject::getEventRepository()->create(this,EVT_ILLEGAL_DP_ACCESS);
        return DataPool::isValid(id);
    }
    if ( type[id] == -1 ) {
        CC_RootObject::getEventRepository()->create(this,EVT_ILLEGAL_DP_ACCESS);
        return DataPool::isValid(id);
    }
    return valid[id];
}

void DC_SampleFullDataPool::setValidityStatus(TD_DataPoolId id, bool newValidityStatus) {
    assert( id <= maxParId );       
    assert( type[id] != -1 );
 
    if ( id > maxParId ) {
        CC_RootObject::getEventRepository()->create(this,EVT_ILLEGAL_DP_ACCESS);
        return;
    }
 
    if ( valid[id] && !newValidityStatus)       // change from valid to not valid
        pDataItem[id]->setVariable((TD_Integer*)pBackUpValue[id]);   // make the data item point to the backup value
    if ( !valid[id] && newValidityStatus)       // change from not valid to valid
        pDataItem[id]->setVariable((TD_Integer*)pValue[id]);         // make the data item point to the primary value
 
    valid[id] = newValidityStatus;
}

MonitoringProfile* DC_SampleFullDataPool::getMonitoringProfile(TD_DataPoolId id) {
    assert( id <= maxParId );       
    assert( type[id] != -1 );
 
    if ( id > maxParId ) {
        CC_RootObject::getEventRepository()->create(this,EVT_ILLEGAL_DP_ACCESS);
        return DataPool::getMonitoringProfile(id);
    }
    if ( type[id] == -1 ) {
        CC_RootObject::getEventRepository()->create(this,EVT_ILLEGAL_DP_ACCESS);
        return DataPool::getMonitoringProfile(id);
    }
    return pMonitoringProfile[id];
}

void DC_SampleFullDataPool::setMonitoringProfile(TD_DataPoolId id, MonitoringProfile* pMonProf) {
    assert( pMonProf != pNULL );
    assert( id <= maxParId );           
    assert( type[id] != -1 );
 
    if ( id > maxParId ) {
        CC_RootObject::getEventRepository()->create(this,EVT_ILLEGAL_DP_ACCESS);
        return;
    }
    if ( type[id] == -1 ) {
        CC_RootObject::getEventRepository()->create(this,EVT_ILLEGAL_DP_ACCESS);
        return;
    }
    pMonitoringProfile[id] = pMonProf;
}

RecoveryAction* DC_SampleFullDataPool::getRecoveryAction(TD_DataPoolId id) {
    assert( id <= maxParId );           
    assert( type[id] != -1 );
 
    if ( id > maxParId ) {
        CC_RootObject::getEventRepository()->create(this,EVT_ILLEGAL_DP_ACCESS);
        return DataPool::getRecoveryAction(id);
    }
    if ( type[id] == -1 ) {
        CC_RootObject::getEventRepository()->create(this,EVT_ILLEGAL_DP_ACCESS);
        return DataPool::getRecoveryAction(id);
    }
    return pRecoveryAction[id];
}

void DC_SampleFullDataPool::setRecoveryAction(TD_DataPoolId id, RecoveryAction* pRecAct) {
    assert( pRecAct != pNULL );
    assert( id <= maxParId );               
    assert( type[id] != -1 );
 
    if ( id > maxParId ) {
        CC_RootObject::getEventRepository()->create(this,EVT_ILLEGAL_DP_ACCESS);
        return;
    }
    if ( type[id] == -1 ) {
        CC_RootObject::getEventRepository()->create(this,EVT_ILLEGAL_DP_ACCESS);
        return;
    }
    pRecoveryAction[id] = pRecAct;
}


TD_DataPoolId DC_SampleFullDataPool::firstIdentifier(void) {
    assert( pValue != pNULL );
    iterationCounter = 0;
    while ( (pValue[iterationCounter]==pNULL) && (iterationCounter<maxParId) )
        iterationCounter++;
    return iterationCounter;
}

TD_DataPoolId DC_SampleFullDataPool::nextIdentifier(void) {
    assert( pValue != pNULL );
    iterationCounter++;
    while ( (pValue[iterationCounter]==pNULL) && (iterationCounter<maxParId) )
        iterationCounter++;
    return iterationCounter;
}

bool DC_SampleFullDataPool::isLastIdentifier(void) {
    assert( pValue != pNULL );
    return ( iterationCounter > maxParId );
}


bool DC_SampleFullDataPool::isFloat(TD_DataPoolId id) {
    assert( id <= maxParId );           
    assert( type[id] != -1 );
 
    if ( id > maxParId ) {
        CC_RootObject::getEventRepository()->create(this,EVT_ILLEGAL_DP_ACCESS);
        return DataPool::isFloat(id);
    }
    if ( type[id] == -1 ) {
        CC_RootObject::getEventRepository()->create(this,EVT_ILLEGAL_DP_ACCESS);
        return DataPool::isFloat(id);
    }
    return ( type[id] == TD_FloatCode );
}

bool DC_SampleFullDataPool::isInteger(TD_DataPoolId id) {
    assert( id <= maxParId );       
    assert( type[id] != -1 );
 
    if ( id > maxParId ) {
        CC_RootObject::getEventRepository()->create(this,EVT_ILLEGAL_DP_ACCESS);
        return DataPool::isInteger(id);
    }
    if ( type[id] == -1 ) {
        CC_RootObject::getEventRepository()->create(this,EVT_ILLEGAL_DP_ACCESS);
        return DataPool::isInteger(id);
    }
    return ( type[id] == TD_IntegerCode );
}

bool DC_SampleFullDataPool::isObjectConfigured(void) {

   // Check configuration of super object
   if (!DataPool::isObjectConfigured()||(pObsClock==pNULL))
       return NOT_CONFIGURED;

   for (TD_DataPoolId i=firstIdentifier(); !isLastIdentifier(); i=nextIdentifier())
        if ( (getMonitoringProfile(i)==pNULL) || (getRecoveryAction(i)==pNULL) )
            return false;

   return true;
}

void DC_SampleFullDataPool::reset(void) {
   for (TD_DataPoolId i=firstIdentifier(); !isLastIdentifier(); i=nextIdentifier())
        setValidityStatus(i, true);
}
