  
//
// Copyright 2003 P&P Software GmbH - All Rights Reserved
//
// TestCaseSampleMonitoredDataPool_1.h
//
// Version	1.0
// Date		10.09.03 (Version 1.0)
// Author	A. Pasetti (P&P Software)
//

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../Data/DC_SampleMonitoredDataPool.h"
#include "../Data/DC_DataItem.h"
#include "../System/DC_DummyObsClock.h"
#include "../FDIR/DC_NullProfile.h"
#include "../FDIR/DC_NullRecoveryAction.h"
#include "TestCaseSampleMonitoredDataPool_1.h"
#include "../Utilities/TestCaseWithEvtCheck.h"

#include <math.h>
#include <float.h>

TestCaseSampleMonitoredDataPool_1::TestCaseSampleMonitoredDataPool_1():
      TestCaseWithEvtCheck(ID_SAMPLEMONITOREDDATAPOOL*10+1,"TestCaseSampleMonitoredDataPool_1") {
            return;
}

void TestCaseSampleMonitoredDataPool_1::runTestCase() {

    // Variable to hold the number of events
    unsigned int nEvt;
    nEvt = getNumberOfEvents();

    // Variable to hold number of parameters in the data pool
    TD_DataPoolId numberOfPar = 8;

    // Instantiate datapool
    DC_SampleMonitoredDataPool* pDP = new DC_SampleMonitoredDataPool();

    // Variable to hold maximum parameter identifier
    TD_DataPoolId maxParId;
    maxParId = 11;

    // Auxiliary variable to hold a data pool item identifier
    TD_DataPoolId id;
    id = 0;

    // Variable to hold the lowest illegal parameter id
    TD_DataPoolId lowestIllegalParId;
    lowestIllegalParId = (TD_DataPoolId)3;

    // Verify correctness of class ID
    if (pDP->getClassId() != ID_SAMPLEMONITOREDDATAPOOL)
    {      setTestResult(TEST_FAILURE, "Wrong class ID");
            return;
    }

    // Check default value of validity status.
    
    if ( !pDP->isValid(1) )
    {      setTestResult(TEST_FAILURE, "Wrong default validity status on data item 1");
            return;
    }
    
    if ( !pDP->isValid(2) )
    {      setTestResult(TEST_FAILURE, "Wrong default validity status on data item 2");
            return;
    }
    
    if ( !pDP->isValid(4) )
    {      setTestResult(TEST_FAILURE, "Wrong default validity status on data item 4");
            return;
    }
    
    if ( !pDP->isValid(5) )
    {      setTestResult(TEST_FAILURE, "Wrong default validity status on data item 5");
            return;
    }
    
    if ( !pDP->isValid(7) )
    {      setTestResult(TEST_FAILURE, "Wrong default validity status on data item 7");
            return;
    }
    
    if ( !pDP->isValid(8) )
    {      setTestResult(TEST_FAILURE, "Wrong default validity status on data item 8");
            return;
    }
    
    if ( !pDP->isValid(10) )
    {      setTestResult(TEST_FAILURE, "Wrong default validity status on data item 10");
            return;
    }
    
    if ( !pDP->isValid(11) )
    {      setTestResult(TEST_FAILURE, "Wrong default validity status on data item 11");
            return;
    }
    
    // Check that the data pool is not yet configured
    if ( pDP->isObjectConfigured() != NOT_CONFIGURED )
    {      setTestResult(TEST_FAILURE, "Incorrect configuration status at creation");
            return;
    }

    // Load monitoring profiles and check correctness of load operations
    DC_NullProfile* pNP = new DC_NullProfile();  
    pDP->setMonitoringProfile(1,pNP);
    if (pDP->getMonitoringProfile(1)!=pNP)
    {	setTestResult(TEST_FAILURE, "Failure to read back monitoring profile");
        return;
    }
    
    pDP->setMonitoringProfile(2,pNP);
    if (pDP->getMonitoringProfile(2)!=pNP)
    {	setTestResult(TEST_FAILURE, "Failure to read back monitoring profile");
        return;
    }
    
    pDP->setMonitoringProfile(4,pNP);
    if (pDP->getMonitoringProfile(4)!=pNP)
    {	setTestResult(TEST_FAILURE, "Failure to read back monitoring profile");
        return;
    }
    
    pDP->setMonitoringProfile(5,pNP);
    if (pDP->getMonitoringProfile(5)!=pNP)
    {	setTestResult(TEST_FAILURE, "Failure to read back monitoring profile");
        return;
    }
    
    pDP->setMonitoringProfile(7,pNP);
    if (pDP->getMonitoringProfile(7)!=pNP)
    {	setTestResult(TEST_FAILURE, "Failure to read back monitoring profile");
        return;
    }
    
    pDP->setMonitoringProfile(8,pNP);
    if (pDP->getMonitoringProfile(8)!=pNP)
    {	setTestResult(TEST_FAILURE, "Failure to read back monitoring profile");
        return;
    }
    
    pDP->setMonitoringProfile(10,pNP);
    if (pDP->getMonitoringProfile(10)!=pNP)
    {	setTestResult(TEST_FAILURE, "Failure to read back monitoring profile");
        return;
    }
    
    pDP->setMonitoringProfile(11,pNP);
    if (pDP->getMonitoringProfile(11)!=pNP)
    {	setTestResult(TEST_FAILURE, "Failure to read back monitoring profile");
        return;
    }
    
    // Check that the data pool is configured
    if ( pDP->isObjectConfigured() != CONFIGURED )
     {      setTestResult(TEST_FAILURE, "Incorrect configuration status");
            return;
      }

    // Check data setting and getting services for the data pool item values
    // Do it for the real-value items first and then for the interger-valued items

    id = 2;
    pDP->setValue(id,(TD_Float)id);
    if ( fabs((float)(pDP->getFloatValue(id)-id))>FLT_EPSILON )
    {	setTestResult(TEST_FAILURE, "Failure to read back data pool item with ID: id");
        return;
    }
    if ( fabs((float)((*pDP->getPointerFloatValue(id))-id))>FLT_EPSILON )
    {	setTestResult(TEST_FAILURE, "Failure to read back data pool item with ID: id");
        return;
    }
    id = 5;
    pDP->setValue(id,(TD_Float)id);
    if ( fabs((float)(pDP->getFloatValue(id)-id))>FLT_EPSILON )
    {	setTestResult(TEST_FAILURE, "Failure to read back data pool item with ID: id");
        return;
    }
    if ( fabs((float)((*pDP->getPointerFloatValue(id))-id))>FLT_EPSILON )
    {	setTestResult(TEST_FAILURE, "Failure to read back data pool item with ID: id");
        return;
    }
    id = 8;
    pDP->setValue(id,(TD_Float)id);
    if ( fabs((float)(pDP->getFloatValue(id)-id))>FLT_EPSILON )
    {	setTestResult(TEST_FAILURE, "Failure to read back data pool item with ID: id");
        return;
    }
    if ( fabs((float)((*pDP->getPointerFloatValue(id))-id))>FLT_EPSILON )
    {	setTestResult(TEST_FAILURE, "Failure to read back data pool item with ID: id");
        return;
    }
    id = 11;
    pDP->setValue(id,(TD_Float)id);
    if ( fabs((float)(pDP->getFloatValue(id)-id))>FLT_EPSILON )
    {	setTestResult(TEST_FAILURE, "Failure to read back data pool item with ID: id");
        return;
    }
    if ( fabs((float)((*pDP->getPointerFloatValue(id))-id))>FLT_EPSILON )
    {	setTestResult(TEST_FAILURE, "Failure to read back data pool item with ID: id");
        return;
    }
    id = 1;
    pDP->setValue(id,(TD_Integer)id);
    if ( pDP->getIntegerValue(id)!=id )
    {	setTestResult(TEST_FAILURE, "Failure to read back data pool item with ID: id");
        return;
    }
    if ( (*pDP->getPointerIntegerValue(id))!=id )
    {	setTestResult(TEST_FAILURE, "Failure to read back data pool item with ID: id");
        return;
    }
    id = 4;
    pDP->setValue(id,(TD_Integer)id);
    if ( pDP->getIntegerValue(id)!=id )
    {	setTestResult(TEST_FAILURE, "Failure to read back data pool item with ID: id");
        return;
    }
    if ( (*pDP->getPointerIntegerValue(id))!=id )
    {	setTestResult(TEST_FAILURE, "Failure to read back data pool item with ID: id");
        return;
    }
    id = 7;
    pDP->setValue(id,(TD_Integer)id);
    if ( pDP->getIntegerValue(id)!=id )
    {	setTestResult(TEST_FAILURE, "Failure to read back data pool item with ID: id");
        return;
    }
    if ( (*pDP->getPointerIntegerValue(id))!=id )
    {	setTestResult(TEST_FAILURE, "Failure to read back data pool item with ID: id");
        return;
    }
    id = 10;
    pDP->setValue(id,(TD_Integer)id);
    if ( pDP->getIntegerValue(id)!=id )
    {	setTestResult(TEST_FAILURE, "Failure to read back data pool item with ID: id");
        return;
    }
    if ( (*pDP->getPointerIntegerValue(id))!=id )
    {	setTestResult(TEST_FAILURE, "Failure to read back data pool item with ID: id");
        return;
    }
    // Check the setting/getting of the validity status
    id = 1;
    pDP->setValidityStatus(id,false);
    if ( pDP->isValid(id) )
    {      setTestResult(TEST_FAILURE, "Wrong validity status");
           return;
    }

    // Check illegal attempt to set the validity status
    if (isNonNominalCheckAllowed()) {
        pDP->setValidityStatus(11+1,false);
        if ( !verifyLatestEvent(nEvt+1,EVT_ILLEGAL_DP_ACCESS) )
            return;
        nEvt = nEvt+1;
    }

    // Reset the data pool and check that all items are valid
    id = 1;
    pDP->setValidityStatus(id,false);
    pDP->reset();
    if ( !pDP->isValid(id) )
    {      setTestResult(TEST_FAILURE, "Reset failure");
           return;
    }


    // Check the back-up value mechanism  (for an integer-valued data pool item)
    id = 1;
    TD_Integer oldValue = pDP->getIntegerValue(id);
    pDP->setValidityStatus(id,false);
    pDP->setValue(id,(TD_Integer)(oldValue+1));
    if ( pDP->getIntegerValue(id)!=oldValue )
    {      setTestResult(TEST_FAILURE, "Back-up value failure");
            return;
    }
    if ( pDP->getDataItem(id)->getIntegerValue()!=oldValue )
    {	setTestResult(TEST_FAILURE, "Back-up value failure");
        return;
    }
    pDP->setValidityStatus(id,true);
    pDP->setValue(id,(TD_Integer)(oldValue+1));
    if ( pDP->getIntegerValue(id)!=(oldValue+1) )
    {      setTestResult(TEST_FAILURE, "Back-up value failure");
           return;
    }
    if ( pDP->getDataItem(id)->getIntegerValue()!=(oldValue+1) )
    {      setTestResult(TEST_FAILURE, "Back-up value failure");
           return;
    }

    // Check the back-up value mechanism  (for a real-valued data pool item)
    id = 2;
    TD_Float fOldValue = pDP->getFloatValue(id);
    pDP->setValidityStatus(id,false);
    pDP->setValue(id,(TD_Float)(fOldValue+1.0));
    if ( fabs( (float)(pDP->getFloatValue(id)-fOldValue) )>FLT_EPSILON )
    {      setTestResult(TEST_FAILURE, "Back-up value failure");
           return;
    }
    pDP->setValidityStatus(id,true);
    pDP->setValue(id,(TD_Float)(fOldValue+1.0));
    if ( fabs( (float)(pDP->getFloatValue(id)-(fOldValue+1.0)) )>FLT_EPSILON )
    {      setTestResult(TEST_FAILURE, "Back-up value failure");
           return;
    }

    // Check the iteration service
    TD_DataPoolId counter = 0;
    for (TD_DataPoolId i=pDP->firstIdentifier(); !pDP->isLastIdentifier(); i=pDP->nextIdentifier()) {
        counter++;
        pDP->setValidityStatus(i,false);        // dummy call -- just to exercise data pool access
    }
    if ( counter!=numberOfPar )
    {   setTestResult(TEST_FAILURE, "Error in data pool iteration");
        return;
    }

   setTestResult(TEST_SUCCESS,"Test Successful");
   return;
}
