//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseDummyTelecommandLoader_1.h
//
// Version	1.0
// Date		11.12.02
// Author	A. Pasetti (P&P Software)

#ifndef TestCaseDummyTelecommandLoader_1H
#define TestCaseDummyTelecommandLoader_1H

#include "../Utilities/TestCaseGenericSetUp.h"

/**
 * Verify the services offered by the <code>DC_DummyTelecommandLoader</code>
 * class.
 * An instance of this class is created and the following specific
 * tests are performed: <ol>
 * <li>The correctness of the class identifier is verified.</li>
 * <li>It is verified that the configuration check service of the telecommand
 * loader initially reports "object not configured".</li>
 * <li>A telecommand manager and three sample telecommands are loaded
 * into the telecommand loader
 * and it is verified that the configuration check service of the telecommand
 * loader reports "object configured".</li>
 * <li>Two activation requests are sent to the telecommand loader and
 * it is verified that the allocation counter is incremented by two.</li>
 * </ol>
 * @see DC_DummyTelecommandLoader
 * @author Alessandro Pasetti (P&P Software GmbH)
 * @version 1.0
 */
class TestCaseDummyTelecommandLoader_1 : public TestCaseGenericSetUp {

public :

     /**
      * Set the identifier and the name of the test case to, respectively,
      * ID_DUMMYTELECOMMANDLOADER*10+1 and "TestCaseDummyTelecommandLoader_1".
      */
     TestCaseDummyTelecommandLoader_1(void);

     /**
      * Execute the test case. See class comment for details.
      */
     virtual void runTestCase(void);
};

#endif
