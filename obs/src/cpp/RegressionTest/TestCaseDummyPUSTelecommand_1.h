//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseDummyPUSTelecommand_1.h
//
// Version	1.1
// Date		11.06.03
// Author	A. Pasetti (P&P Software)

#ifndef TestCaseDummyPUSTelecommand_1H
#define TestCaseDummyPUSTelecommand_1H

#include "../Utilities/TestCaseGenericSetUp.h"

/**
 * Check the functionalities implemented in the <code>PUSTelecommand</code> class.
 * Since this class is abstract, it is tested through its concrete subclass
 * <code>DC_DummyPUSTelecommand</code>.
 * An instance of this class is created and the following specific
 * tests are performed: <ol>
 * <li>The correctness of the class identifier is checked.</li>
 * <li>It is checked that the telecommand is not configured.</li>
 * <li>The time tag is set and read back and the correctness of the read-back
 * value is checked.</li>
 * <li>The telecommand identifier is read out and its correctness is checked.</li>
 * <li>The telecommand type is read out and its correctness is checked.</li>
 * <li>The telecommand subtype read out and its correctness is checked.</li>
 * <li>The telecommand acknowledge level is read out and its correctness is checked.</li>
 * <li>The packet identifier is read and the correctness of its value is checked.</li>
 * <li>The telecommand ackowledge level is updated and it is checked that
 * the value of the acceptance flag, the start flag, the progress flag
 * and the completion flags are consistent with the value of the acknoledge level attribute.</li>
 * <li>It is verified that the configuration service of the telecommand
 * now reports "telecommand is configured".</li>
 * <li>It is verified that the initial value of the execution counter
 * is equal to zero.</li>
 * <li>Two execution requests are sent to the telecommand and it is
 * verified that the execution counter is incremented by two.</li>
 * </ol>
 * @see DC_DummyPUSTelecommand
 * @author Alessandro Pasetti (P&P Software GmbH)
 * @version 1.0
 */
class TestCaseDummyPUSTelecommand_1 : public TestCaseGenericSetUp {

public :

     /**
      * Set the identifier and the name of the test case to, respectively,
      * ID_DUMMYPUSTELECOMMAND*10+1 and "TestCaseDummyPUSTelecommand_1".
      */
     TestCaseDummyPUSTelecommand_1(void);

     /**
      * Execute the test case. See class comment for details.
      */
     virtual void runTestCase(void);
};

#endif
