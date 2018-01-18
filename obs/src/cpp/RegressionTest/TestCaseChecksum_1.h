//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseChecksum_1.h
//
// Version	1.0
// Date		13.01.04
// Author	A. Pasetti (P&P Software)

#ifndef TestCaseChecksum_1H
#define TestCaseChecksum_1H

#include "../Utilities/TestCaseGenericSetUp.h"

/**
 * Check the checksum functions provided in module <code>Checksum</code>.
 * The following specific tests are performed: <ol>
 * <li>The checksum of a stream of bytes is computed and the correctness of
 * of the computed value is checked.</li>
 * <li>A checksum check is performed over a stream of bytes and the correctness
 * of the check result is verifed.</li>
 * </ol>
 * The sample stream of data are taken from section A.2.5 of the PUS standard.
 * @author Alessandro Pasetti (P&P Software GmbH)
 * @version 1.0
 */
class TestCaseChecksum_1 : public TestCaseGenericSetUp {

public :

     /**
      * Set the identifier and the name of the test case to, respectively,
      * ID_CHECKSUM*10+1 and "TestCaseChecksum_1".
      */
     TestCaseChecksum_1(void);

     /**
      * Execute the test case. See class comment for details.
      */
	virtual void runTestCase(void);
};

#endif
