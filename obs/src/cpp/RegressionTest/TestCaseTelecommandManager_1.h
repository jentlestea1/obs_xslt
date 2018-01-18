//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseTelecommandManager_1.h
//
// Version	1.0
// Date		11.12.02
// Author	A. Pasetti (P&P Software)

#ifndef TestCaseTelecommandManager_1H
#define TestCaseTelecommandManager_1H

#include "../Utilities/TestCaseGenericSetUp.h"

/**
 * Check the configuration process of a telecommand manager.
 * A telecommand manager instance is created and the following specific
 * tests are performed: <ol>
 * <li>The correctness of the class identifier is verified.</li>
 * <li>It is verified that the configuration check service of the telecommand
 * manager initially reports "object not configured".</li>
 * <li>An OBS clock is loaded in the telecommand manager and it is verified
 * that it can be correctly read out.</li>
 * <li>A telecommand loader is loaded in the telecommand manager and it is verified
 * that it can be correctly read out.</li>
 * <li>The pending telecommand list size is set and it is verified
 * that it can be correctly read out.</li>
 * <li>It is verified that the configuration check service of the telecommand
 * manager now reports "object configured".</li>
 * <li>It is verified that the number of pending telecommands is equal to
 * zero.</li>
 * </ol>
 * @see CC_TelecommandManager
 * @author Alessandro Pasetti (P&P Software GmbH)
 * @version 1.0
 */
class TestCaseTelecommandManager_1 : public TestCaseGenericSetUp {

public :

     /**
      * Set the identifier and the name of the test case to, respectively,
      * ID_TELECOMMANDMANAGER*10+1 and "TestCaseTelecommandManager_1".
      */
     TestCaseTelecommandManager_1(void);

     /**
      * Execute the test case. See class comment for details.
      */
     virtual void runTestCase(void);
};

#endif
