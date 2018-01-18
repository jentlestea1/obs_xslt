//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseDummyDataPool_1.cpp
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
#include "../Data/DC_DummyDataPool.h"
#include "TestCaseDummyDataPool_1.h"

TestCaseDummyDataPool_1::TestCaseDummyDataPool_1(void) :
	TestCaseGenericSetUp(ID_DUMMYDATAPOOL*10+1,"TestCaseDummyDataPool_1") {
		return;
}

void TestCaseDummyDataPool_1::runTestCase(void) {

   // Instantiate dummy datapool
   DC_DummyDataPool* pDP = new DC_DummyDataPool();

   // Check class identifier
   if (pDP->getClassId() != ID_DUMMYDATAPOOL)
	{	setTestResult(TEST_FAILURE, "Wrong class ID");
		return;
	}

   // Check size and value of data pool item
    if ( pDP->getDataPoolSize() != sizeof(TD_Integer) )
	{	setTestResult(TEST_FAILURE, "Incorrect size of the data pool");
		return;
	}

    if ( pDP->getIntegerValue(0) != (TD_Integer)0 )
	{	setTestResult(TEST_FAILURE, "Incorrect value of data pool item");
		return;
	}

	setTestResult(TEST_SUCCESS,"Test Successful");
	return;
}
