  
//
// Copyright 2003 P&P Software GmbH - All Rights Reserved
//
// DC_SampleMonitoredDataPool.cpp
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
#include "DC_SampleMonitoredDataPool.h"

static unsigned int const TD_FloatCode = 1;
static unsigned int const TD_IntegerCode = 2;

DC_SampleMonitoredDataPool::DC_SampleMonitoredDataPool(void) {
   setClassId(ID_SAMPLEMONITOREDDATAPOOL);

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
   valid = new bool[maxParId+1];   
   pDataItem = new DC_SettableDataItem*[maxParId+1];    
   pMonitoringProfile = new MonitoringProfile*[maxParId+1];       

   for (TD_DataPoolId i=0; i<size; i++)  {
        value[i] = 0;  
        backUpValue[i] = 0;          
   }

   for (TD_DataPoolId i=0; i<=maxParId; i++)  {
        pValue[i] = pNULL;         
        pBackUpValue[i] = pNULL;          
        valid[i] = true;                
        pDataItem[i] = pNULL;   
        pMonitoringProfile[i] = pNULL;          
   }

 unsigned int offset = 0;           
 // Store the TD_Float values in the first part of the array
     
 pValue[2] = value + offset;               
 pBackUpValue[2] = backUpValue + offset;   
 offset = offset + sizeof(TD_Float);              
 pDataItem[2] = new DC_SettableDataItem((TD_Float*)pValue[2]); 
        
 pValue[5] = value + offset;               
 pBackUpValue[5] = backUpValue + offset;   
 offset = offset + sizeof(TD_Float);              
 pDataItem[5] = new DC_SettableDataItem((TD_Float*)pValue[5]); 
        
 pValue[8] = value + offset;               
 pBackUpValue[8] = backUpValue + offset;   
 offset = offset + sizeof(TD_Float);              
 pDataItem[8] = new DC_SettableDataItem((TD_Float*)pValue[8]); 
        
 pValue[11] = value + offset;               
 pBackUpValue[11] = backUpValue + offset;   
 offset = offset + sizeof(TD_Float);              
 pDataItem[11] = new DC_SettableDataItem((TD_Float*)pValue[11]); 
        
 // Now ensure that offset is aligned with a TD_Integer
 unsigned int temp = (offset/sizeof(TD_Integer));
 if (temp*sizeof(TD_Integer)<offset)
    offset = (temp+1)*sizeof(TD_Integer);

 // Store the TD_Integer values in the second part of the array
     
 pValue[1] = value + offset;               
 pBackUpValue[1] = backUpValue + offset;   
 offset = offset + sizeof(TD_Integer);              
 pDataItem[1] = new DC_SettableDataItem((TD_Integer*)pValue[1]); 
        
 pValue[4] = value + offset;               
 pBackUpValue[4] = backUpValue + offset;   
 offset = offset + sizeof(TD_Integer);              
 pDataItem[4] = new DC_SettableDataItem((TD_Integer*)pValue[4]); 
        
 pValue[7] = value + offset;               
 pBackUpValue[7] = backUpValue + offset;   
 offset = offset + sizeof(TD_Integer);              
 pDataItem[7] = new DC_SettableDataItem((TD_Integer*)pValue[7]); 
        
 pValue[10] = value + offset;               
 pBackUpValue[10] = backUpValue + offset;   
 offset = offset + sizeof(TD_Integer);              
 pDataItem[10] = new DC_SettableDataItem((TD_Integer*)pValue[10]); 
        

}

 

void DC_SampleMonitoredDataPool::setValue(TD_DataPoolId id, TD_Float newValue) {
    assert( id <= maxParId );               
    (*(TD_Float*)pValue[id]) = newValue;        
    if ( valid[id] )
        (*(TD_Float*)pBackUpValue[id]) = newValue;          
}

void DC_SampleMonitoredDataPool::setValue(TD_DataPoolId id, TD_Integer newValue) {
    assert( id <= maxParId );           
    (*(TD_Integer*)pValue[id]) = newValue;      
    if ( valid[id] )
        (*(TD_Integer*)pBackUpValue[id]) = newValue;        
}

TD_Float DC_SampleMonitoredDataPool::getFloatValue(TD_DataPoolId id) {
    assert( id <= maxParId );           
    if ( valid[id] )
        return (*(TD_Float*)pValue[id]);
    else
        return (*(TD_Float*)pBackUpValue[id]);
   
}

TD_Integer DC_SampleMonitoredDataPool::getIntegerValue(TD_DataPoolId id) {
    assert( id <= maxParId );           
    if ( valid[id] )
        return (*(TD_Integer*)pValue[id]);
    else
        return (*(TD_Integer*)pBackUpValue[id]);
   
}

TD_Float* DC_SampleMonitoredDataPool::getPointerFloatValue(TD_DataPoolId id) {
    assert( id <= maxParId );           
    return ((TD_Float*)pValue[id]);
}

TD_Integer* DC_SampleMonitoredDataPool::getPointerIntegerValue(TD_DataPoolId id) {
    assert( id <= maxParId );           
    return ((TD_Integer*)pValue[id]);
}

 
DC_DataItem* DC_SampleMonitoredDataPool::getDataItem(TD_DataPoolId id) {
    assert( id <= maxParId );           
    return pDataItem[id];
}
 
bool DC_SampleMonitoredDataPool::isValid(TD_DataPoolId id) {
    assert( id <= maxParId );               
    return valid[id];
}

void DC_SampleMonitoredDataPool::setValidityStatus(TD_DataPoolId id, bool newValidityStatus) {
    assert( id <= maxParId );       
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

MonitoringProfile* DC_SampleMonitoredDataPool::getMonitoringProfile(TD_DataPoolId id) {
    assert( id <= maxParId );       
    return pMonitoringProfile[id];
}

void DC_SampleMonitoredDataPool::setMonitoringProfile(TD_DataPoolId id, MonitoringProfile* pMonProf) {
    assert( pMonProf != pNULL );
    assert( id <= maxParId );           
    pMonitoringProfile[id] = pMonProf;
}


TD_DataPoolId DC_SampleMonitoredDataPool::firstIdentifier(void) {
    assert( pValue != pNULL );
    iterationCounter = 0;
    while ( (pValue[iterationCounter]==pNULL) && (iterationCounter<maxParId) )
        iterationCounter++;
    return iterationCounter;
}

TD_DataPoolId DC_SampleMonitoredDataPool::nextIdentifier(void) {
    assert( pValue != pNULL );
    iterationCounter++;
    while ( (pValue[iterationCounter]==pNULL) && (iterationCounter<maxParId) )
        iterationCounter++;
    return iterationCounter;
}

bool DC_SampleMonitoredDataPool::isLastIdentifier(void) {
    assert( pValue != pNULL );
    return ( iterationCounter > maxParId );
}


bool DC_SampleMonitoredDataPool::isObjectConfigured(void) {

   // Check configuration of super object
   if (!DataPool::isObjectConfigured())
       return NOT_CONFIGURED;

   for (TD_DataPoolId i=firstIdentifier(); !isLastIdentifier(); i=nextIdentifier())
        if ( (getMonitoringProfile(i)==pNULL) || (getRecoveryAction(i)==pNULL) )
            return false;

   return true;
}

void DC_SampleMonitoredDataPool::reset(void) {
   for (TD_DataPoolId i=firstIdentifier(); !isLastIdentifier(); i=nextIdentifier())
        setValidityStatus(i, true);
}
