//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseNullProfile_1.cpp
//
// Version	1.0
// Date		01.10.03
// Author	R. Totaro

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../FDIR/DC_NullProfile.h"
#include "TestCaseNullProfile_1.h"

TestCaseNullProfile_1::TestCaseNullProfile_1(void) :
    TestCaseGenericSetUp(ID_NULLPROFILE*10+1,"TestCaseNullProfile_1") {
    return;
}

void TestCaseNullProfile_1::runTestCase(void) {
    DC_NullProfile    *pNP       =new DC_NullProfile;
    const unsigned int iterations=100;

    // Check the value of the class identifier
    if (pNP->getClassId()!=ID_NULLPROFILE ) {
        setTestResult(TEST_FAILURE,"Wrong class identifier");
        return;
    }

    for (TD_Integer i=0;i<iterations;i++) {
        TD_Float   fVal=(TD_Float)0.1*i;
        TD_Integer iVal=(TD_Integer)12*i;

        if (pNP->deviatesFromProfile(fVal)) {
            setTestResult(TEST_FAILURE,"deviatesFromProfile(TD_Float) failed");
            return;
        }

        if (pNP->deviatesFromProfile(iVal)) {
            setTestResult(TEST_FAILURE,"deviatesFromProfile(TD_Integer) failed");
            return;
        }
    }

    // Do dummy call to reset
    pNP->reset();

    setTestResult(TEST_SUCCESS,"Test Successful");
    return;
}
