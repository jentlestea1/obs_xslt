//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseDummyObsClock_1.h
//
// Version	1.0
// Date		13.09.02
// Author	     A. Pasetti (P&P Software)

#ifndef TestCaseDummyObsClock_1H
#define TestCaseDummyObsClock_1H

#include "../Utilities/TestCaseGenericSetUp.h"

/**
 * Verify the timing provision and object configuration services of class
 * <code>DC_DummyObsClock</code>.
 * The following specific tests are performed: <ol>
 * <li>A <code>DC_DummyObsClock</code> instance is created and it is verified
 * that its object configuration service reports "object configured".</li>
 * <li>The OBS time and cycle services are called on the newly created object
 * and it is verified that they report 0.</li>
 * <li>The OBS time and cycle are set with the <code>setTime</code> service and
 * it is then verified that the OBS time and cycle services report the newly
 * set values.</li>
 * <li>The Dummy OBS Clock component is reset and it is verified that its time
 * and cycle data are reset to 0.</li>
 * <li>A dummy call to method <code>synchronizeWithSystemTime</code> is done.
 * This is necessary to ensure full statement coverage of the class under test.</li>
 * </ol>
 * @author Alessandro Pasetti (P&P Software GmbH)
 * @version 1.0
 */
class TestCaseDummyObsClock_1 : public TestCaseGenericSetUp {

public :

     /**
      * Set the identifier and the name of the test case to, respectively,
      * ID_OBSDUMMYCLOCK*10+1 and "TestCaseDummyObsClock_1".
      */
     TestCaseDummyObsClock_1(void);

     /**
      * Execute the test case. See class comment for details.
      */
	virtual void runTestCase(void);
};

#endif
