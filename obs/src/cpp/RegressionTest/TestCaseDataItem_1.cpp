//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseDataItem_1.cpp
//
// Version	2.0
// Date		17.04.03 (Version 1.1)
//          11.06.03 (Version 2.0)
// Author	R. Totaro
//
// Change Record:
//   Version 2.0: Adapted to the new DC_DataItem class interface.

#include <math.h>
#include <float.h>

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/TestCompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/TestConstants.h"
#include "../Data/DC_DataItem.h"
#include "TestCaseDataItem_1.h"

TestCaseDataItem_1::TestCaseDataItem_1(void) :
	TestCaseGenericSetUp(ID_DATAITEM*10+1,"TestCaseDataItem_1") {
	return;
}

void TestCaseDataItem_1::runTestCase(void) {
	TD_Float       fv;
	TD_Integer     iv;
	DC_DataItem   *pFDI = new DC_DataItem(&fv);
	DC_DataItem   *pIDI = new DC_DataItem(&iv);

	// Check the working of the getter methods
	iv = (TD_Integer)41;
	if (pIDI->getIntegerValue()!=(TD_Integer)41) {
		setTestResult(TEST_FAILURE,"getInteger() failed");
		return;
	}

	fv = (TD_Float)41;
	if (pFDI->getFloatValue()!=(TD_Float)41) {
		setTestResult(TEST_FAILURE,"getFloat() failed");
		return;
	}

	// Verify the setter methods
	pIDI->setValue((TD_Integer)51);
	if (iv!=(TD_Integer)51) {
		setTestResult(TEST_FAILURE,"setInteger() failed");
		return;
	}

	pFDI->setValue((TD_Float)50);
	if (fv!=(TD_Float)50) {
		setTestResult(TEST_FAILURE,"setFloat() failed");
		return;
	}

	setTestResult(TEST_SUCCESS,"Test Successful");
	return;
}
