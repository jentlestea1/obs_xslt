//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseBasicDataPool_1.cpp
//
// Version	1.0
// Date		13.10.03
// Author	A. Pasetti (P&P Software)

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../Data/DC_BasicDatabase.h"
#include "../FDIR/RecoveryAction.h"
#include "../FDIR/MonitoringProfile.h"
#include "../Data/DC_BasicDataPool.h"
#include "../Data/DC_DataItem.h"
#include "TestCaseBasicDataPool_1.h"

#include <math.h>
#include <float.h>

TestCaseBasicDataPool_1::TestCaseBasicDataPool_1(void) :
	TestCaseGenericSetUp(ID_BASICDATAPOOL*10+1,"TestCaseBasicDataPool_1") {
		return;
}

void TestCaseBasicDataPool_1::runTestCase(void) {

   // Data to be written and read back from the data pool together with their identifiers.
   TD_Float f = (TD_Float)2.0;
   TD_Integer i = (TD_Integer)3;
   TD_DataPoolId f_id = 0;
   TD_DataPoolId i_id = sizeof(TD_Float);

   // Instantiate basic datapool
   DC_BasicDataPool* pDP = new DC_BasicDataPool();

   // Verify correctness of class ID
   if (pDP->getClassId() != ID_BASICDATAPOOL)
	{	setTestResult(TEST_FAILURE, "Wrong class ID");
		return;
	}

   // Check that datapool is not yet configured
	if ( pDP->isObjectConfigured() != NOT_CONFIGURED )
	{	setTestResult(TEST_FAILURE, "Incorrect configuration status at creation");
		return;
	}

   // Set data pool size and check correctness
   TD_DataPoolId size = sizeof(TD_Integer)+sizeof(TD_Float);
   pDP->setDataPoolSize(size);
   if ( pDP->getDataPoolSize() != size )
   {    setTestResult(TEST_FAILURE, "Incorrect value for the data pool size");
        return;
   }

   // Check that database is configured
   if ( pDP->isObjectConfigured() != CONFIGURED )
   {    setTestResult(TEST_FAILURE, "Incorrect configuration status after configuration was completed");
        return;
   }

   // Check retrieval of data item attribute
   DC_DataItem* pDI = pDP->getDataItem(3);
   if ( pDI->getIntegerValue() != 0 )
   {    setTestResult(TEST_FAILURE, "Incorrect data item attribute");
	    return;
   }

   // Check retrieval of time stamp attribute
   if ( pDP->getTimeStamp(2) != 0 )
   {    setTestResult(TEST_FAILURE, "Incorrect time stamp attribute");
	    return;
   }

   // Check retrieval of validity attribute
   if ( !pDP->isValid(2) )
   {    setTestResult(TEST_FAILURE, "Incorrect validity attribute");
	    return;
   }

   // Check type checking services
   if ( (!pDP->isFloat(7)) || (!pDP->isInteger(7)) )
   {    setTestResult(TEST_FAILURE, "Incorrect type checking services");
	    return;
   }

   // Check iteration methods
   if ( (pDP->firstIdentifier()!=0) || (pDP->nextIdentifier()!=0) || (!pDP->isLastIdentifier()) )
   {    setTestResult(TEST_FAILURE, "Incorrect iteration services");
	    return;
   }

   // Check retrieval of monitoring profile attribute
   if ( pDP->getMonitoringProfile(2)->getClassId() != ID_NULLPROFILE )
   {    setTestResult(TEST_FAILURE, "Incorrect monitoring profile attribute");
	    return;
   }

   // Check retrieval of recovery action attribute
   if ( pDP->getRecoveryAction(3)->getClassId() != ID_NULLRECOVERYACTION )
   {    setTestResult(TEST_FAILURE, "Incorrect monitoring profile attribute");
	    return;
   }

   // Call reset and validity setter methods (just to show that they can be called without
   // crashing the system)
   pDP->reset();
   pDP->setValidityStatus(0,true);

   // Set and read float value and check correctness
   pDP->setValue(f_id,f);
   if (fabs(pDP->getFloatValue(f_id)-f)>FLT_EPSILON)
   {	setTestResult(TEST_FAILURE, "Incorrect write/read cycle for float value");
    	return;
   }

   // Set and read integer value and check correctness
   pDP->setValue(i_id,i);
   if (pDP->getIntegerValue(i_id)!=i)
   {	setTestResult(TEST_FAILURE, "Incorrect write/read cycle for integer value");
    	return;
   }

   // Check pointer access for float values
   if (fabs( (float) ((*(pDP->getPointerFloatValue(f_id)))-f) )>FLT_EPSILON)
   {	setTestResult(TEST_FAILURE, "Incorrect pointer access to float value");
    	return;
   }

   // Check pointer access for integer values
   if ( (*(pDP->getPointerIntegerValue(i_id)))!=i )
   {	setTestResult(TEST_FAILURE, "Incorrect pointer access to integer value");
    	return;
   }

	setTestResult(TEST_SUCCESS,"Test Successful");
	return;
}
