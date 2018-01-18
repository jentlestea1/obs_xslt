//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseBasicDatabase_1.cpp
//
// Version	1.0
// Date		13.09.02
// Author	A. Pasetti (P&P Software)

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../Data/DC_BasicDatabase.h"
#include "TestCaseBasicDatabase_1.h"

#include <math.h>
#include <float.h>

TestCaseBasicDatabase_1::TestCaseBasicDatabase_1(void) :
	TestCaseGenericSetUp(ID_BASICDATABASE*10+1,"TestCaseBasicDatabase_1") {
		return;
}

void TestCaseBasicDatabase_1::runTestCase(void) {

   // Data structure to simulate the default table
   // NB: In order to avoid alignment problems, make sure that the
   //     table is aligned on a double word boundary
   // NB: The double array is oversized: the intended size of the 
    //    default table is 12 bytes.
   double shadowDefaultTable[3];
   unsigned int* defaultTable = (unsigned int*)shadowDefaultTable;

   // The following data simulate the default table of the basic database.
   // The table is assumed to contain three integer items.
   // NB: this test assumes that the compiler aligns the following three
   //     in continguous memory location.
   defaultTable[0] = 0xAABBCCDD;       // first parameter
   defaultTable[1] = 0x11223344;       // second parameter
   defaultTable[2] = 0x55667788;       // third parameter

   // The following constants represent the parameter identifiers of the
   // three entries in the default table
   const TD_DatabaseId PD_T1 = 0;
   const TD_DatabaseId PD_T2 = 4;
   const TD_DatabaseId PD_T3 = 8;

   // Data structure to simulate the operational table
   // NB: In order to avoid alignment problems, make sure that the
   //     table is aligned on a double word boundary
   double shadowOperationalTable[3];
   int* operationalTable = (int*)shadowOperationalTable;

   // Instantiate basic database
   DC_BasicDatabase* pDB = new DC_BasicDatabase();

   // Verify correctness of class ID
   if (pDB->getClassId() != ID_BASICDATABASE)
	{	setTestResult(TEST_FAILURE, "Wrong class ID");
		return;
	}

    // Check that database is not yet configured
    if ( pDB->isObjectConfigured() != NOT_CONFIGURED )
    {   setTestResult(TEST_FAILURE, "Incorrect configuration status at creation");
        return;
    }

    // Set the table length and check correctness
    pDB->setTableLength(12);
    if ( pDB->getTableLength() != 12 )
    {   setTestResult(TEST_FAILURE, "Incorrect table length");
        return;
    }

   // Complete configuration of the database
   pDB->setDefaultTable((char*)defaultTable);
   pDB->setOperationalTable((char*)operationalTable);
   pDB->reset();

   // Check that database is configured
	if ( pDB->isObjectConfigured() != CONFIGURED )
	{	setTestResult(TEST_FAILURE, "Incorrect configuration status after configuration was completed");
		return;
	}

   // Check that operational table was correctly initialized
   if ( pDB->getParameterUnsignedInt(PD_T1) != defaultTable[0] )
	{	setTestResult(TEST_FAILURE, "Incorrect initialization of operational table");
		return;
	}
   if ( pDB->getParameterUnsignedInt(PD_T2) != defaultTable[1] )
	{	setTestResult(TEST_FAILURE, "Incorrect initialization of operational table");
		return;
	}
   if ( pDB->getParameterUnsignedInt(PD_T3) != defaultTable[2] )
	{	setTestResult(TEST_FAILURE, "Incorrect initialization of operational table");
		return;
	}

   // Check the read/write services for all parameter types
    double d = 0.2;
    pDB->setParameter(PD_T1,d);
    if (fabs(pDB->getParameterDouble(PD_T1)-d)>DBL_EPSILON)
	{	setTestResult(TEST_FAILURE, "Incorrect write/read cycle for double parameter");
		return;
	}
    if (fabs((*pDB->getParameterPointerDouble(PD_T1))-d)>DBL_EPSILON)
	{	setTestResult(TEST_FAILURE, "Incorrect getter method for pointer to double parameter");
		return;
	}

    float f = (float)0.4;
    pDB->setParameter(PD_T2,f);
    if (fabs(pDB->getParameterFloat(PD_T2)-f)>FLT_EPSILON)
	{	setTestResult(TEST_FAILURE, "Incorrect write/read cycle for float parameter");
		return;
	}
    if (fabs((*pDB->getParameterPointerFloat(PD_T2))-f)>FLT_EPSILON)
	{	setTestResult(TEST_FAILURE, "Incorrect getter method for pointer to float parameter");
		return;
	}

    unsigned int ui = 10;
    pDB->setParameter(PD_T2,ui);
    if (pDB->getParameterUnsignedInt(PD_T2)!=ui)
	{	setTestResult(TEST_FAILURE, "Incorrect write/read cycle for unsigned int parameter");
		return;
	}
    if ((*pDB->getParameterPointerUnsignedInt(PD_T2))!=ui)
	{	setTestResult(TEST_FAILURE, "Incorrect getter method for pointer to unsigned int parameter");
		return;
	}

    int i = 20;
    pDB->setParameter(PD_T2,i);
    if (pDB->getParameterInt(PD_T2)!=i)
	{	setTestResult(TEST_FAILURE, "Incorrect write/read cycle for int parameter");
		return;
	}
    if ((*pDB->getParameterPointerInt(PD_T2))!=i)
	{	setTestResult(TEST_FAILURE, "Incorrect getter method for pointer to int parameter");
		return;
	}

    unsigned short us = 40;
    pDB->setParameter(PD_T2,us);
    if (pDB->getParameterUnsignedShort(PD_T2)!=us)
	{	setTestResult(TEST_FAILURE, "Incorrect write/read cycle for unsigned short parameter");
		return;
	}
    if ((*pDB->getParameterPointerUnsignedShort(PD_T2))!=us)
	{	setTestResult(TEST_FAILURE, "Incorrect getter method for pointer to unsigned short parameter");
		return;
	}

    short s = 30;
    pDB->setParameter(PD_T2,s);
    if (pDB->getParameterShort(PD_T2)!=s)
	{	setTestResult(TEST_FAILURE, "Incorrect write/read cycle for short parameter");
		return;
	}
    if ((*pDB->getParameterPointerShort(PD_T2))!=s)
	{	setTestResult(TEST_FAILURE, "Incorrect getter method for pointer to short parameter");
		return;
	}

    unsigned char uc = 4;
    pDB->setParameter(PD_T2,uc);
    if (pDB->getParameterUnsignedChar(PD_T2)!=uc)
	{	setTestResult(TEST_FAILURE, "Incorrect write/read cycle for unsigned char parameter");
		return;
	}
    if ((*pDB->getParameterPointerUnsignedChar(PD_T2))!=uc)
	{	setTestResult(TEST_FAILURE, "Incorrect getter method for pointer to unsigned char parameter");
		return;
	}

    char c = 2;
    pDB->setParameter(PD_T2,c);
    if (pDB->getParameterUnsignedChar(PD_T2)!=c)
	{	setTestResult(TEST_FAILURE, "Incorrect write/read cycle for char parameter");
		return;
	}
    if ((*pDB->getParameterPointerChar(PD_T2))!=c)
	{	setTestResult(TEST_FAILURE, "Incorrect getter method for pointer to char parameter");
		return;
	}

    bool b = true;
    pDB->setParameter(PD_T2,b);
    if (pDB->getParameterBool(PD_T2)!=b)
	{	setTestResult(TEST_FAILURE, "Incorrect write/read cycle for boolean parameter");
		return;
	}
    if ((*pDB->getParameterPointerBool(PD_T2))!=b)
	{	setTestResult(TEST_FAILURE, "Incorrect getter method for pointer to boolean parameter");
		return;
	}


	setTestResult(TEST_SUCCESS,"Test Successful");
	return;
}
