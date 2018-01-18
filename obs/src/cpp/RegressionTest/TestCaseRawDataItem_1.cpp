//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseRawDataItem_1.cpp
//
// Version	1.0
// Date		11.10.03 (Version 2.0)
// Author	R. Totaro, A. Pasetti
//
// Change Record:

#include <math.h>
#include <float.h>

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/TestCompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/TestConstants.h"
#include "../Data/DC_RawDataItem.h"
#include "../Data/DC_DataItem.h"
#include "TestCaseRawDataItem_1.h"

TestCaseRawDataItem_1::TestCaseRawDataItem_1(void) :
	TestCaseGenericSetUp(ID_RAWDATAITEM*10+1,"TestCaseRawDataItem_1") {
	return;
}

void TestCaseRawDataItem_1::runTestCase(void) {
	char           charVal;
	unsigned char  uCharVal;
	short          shortVal;
	unsigned short uShortVal;
	int            intVal;
	unsigned int   uIntVal;
	float          floatVal;
	double         doubleVal;
	DC_RawDataItem   *pCharData  =new DC_RawDataItem(&charVal);
	DC_RawDataItem   *pUCharData =new DC_RawDataItem(&uCharVal);
	DC_RawDataItem   *pShortData =new DC_RawDataItem(&shortVal);
	DC_RawDataItem   *pUShortData=new DC_RawDataItem(&uShortVal);
	DC_RawDataItem   *pIntData   =new DC_RawDataItem(&intVal);
	DC_RawDataItem   *pUIntData  =new DC_RawDataItem(&uIntVal);
	DC_RawDataItem   *pFloatData =new DC_RawDataItem(&floatVal);
	DC_RawDataItem   *pDoubleData=new DC_RawDataItem(&doubleVal);

	// Verify the working of the getter methods
	charVal=-41;
	if (pCharData->getChar()!=-41) {
		setTestResult(TEST_FAILURE,"getChar() failed");
		return;
	}

	uCharVal=42;
	if (pUCharData->getUnsignedChar()!=42) {
		setTestResult(TEST_FAILURE,"getUnsignedChar() failed");
		return;
	}

	shortVal=-43;
	if (pShortData->getShort()!=-43) {
		setTestResult(TEST_FAILURE,"getShort() failed");
		return;
	}

	uShortVal=44;
	if (pUShortData->getUnsignedShort()!=44) {
		setTestResult(TEST_FAILURE,"getUnsignedShort() failed");
		return;
	}

	intVal=-45;
	if (pIntData->getInt()!=-45) {
		setTestResult(TEST_FAILURE,"getInt() failed");
		return;
	}

	uIntVal=46;
	if (pUIntData->getUnsignedInt()!=46) {
		setTestResult(TEST_FAILURE,"getUnsignedInt() failed");
		return;
	}

	floatVal=-47.48f;
	if (fabsf(pFloatData->getFloat()+47.48f)>=FLT_EPSILON) {
		setTestResult(TEST_FAILURE,"getFloat() failed");
		return;
	}

	doubleVal=49.50;
	if (fabs(pDoubleData->getDouble()-49.50)>=DBL_EPSILON) {
		setTestResult(TEST_FAILURE,"getDouble() failed");
		return;
	}

	// Verify the setter methods
	pCharData->setChar(-51);
	if (charVal!=-51) {
		setTestResult(TEST_FAILURE,"setChar() failed");
		return;
	}

	pUCharData->setUnsignedChar(52);
	if (uCharVal!=52) {
		setTestResult(TEST_FAILURE,"setUnsignedChar() failed");
		return;
	}

	pShortData->setShort(-53);
	if (shortVal!=-53) {
		setTestResult(TEST_FAILURE,"setShort() failed");
		return;
	}

	pUShortData->setUnsignedShort(54);
	if (uShortVal!=54) {
		setTestResult(TEST_FAILURE,"setUnsignedShort() failed");
		return;
	}

	pIntData->setInt(-55);
	if (intVal!=-55) {
		setTestResult(TEST_FAILURE,"setInt() failed");
		return;
	}

	pUIntData->setUnsignedInt(56);
	if (uIntVal!=56) {
		setTestResult(TEST_FAILURE,"setUnsignedInt() failed");
		return;
	}

	pFloatData->setFloat(-57.58f);
	if (fabsf(floatVal+57.58f)>=FLT_EPSILON) {
		setTestResult(TEST_FAILURE,"setFloat() failed");
		return;
	}

	pDoubleData->setDouble(59.60);
	if (fabs(doubleVal-59.60)>=DBL_EPSILON) {
		setTestResult(TEST_FAILURE,"setDouble() failed");
		return;
	}

	setTestResult(TEST_SUCCESS,"Test Successful");
	return;
}
