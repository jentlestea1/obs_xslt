//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseTelecommandManager_2.h
//
// Version	1.0
// Date		11.12.02
// Author	A. Pasetti (P&P Software)

#ifndef TestCaseTelecommandManager_2H
#define TestCaseTelecommandManager_2H

#include "../Utilities/TestCaseGenericSetUp.h"

/**
 * Check the configuration the nominal telecommand execution process
 * implemented by the telecommand manager.
 * The test uses an instance of class <code>DC_DummyTelecommandLoader</code>
 * as a telecommand loader and three instances of class
 * <code>DC_DummyTelecommand</code> as dummy telecommands.
 * The third telecommand is configured to have a 0 time-tag (immediate
 * execution) and the first two are configured to have two consecutive
 * time tags.
 * The test begins by creating and configuring a telecommand manager
 * instance and by activating the telecommand loader to make it load
 * all three dummy telecommands. The following specific tests are
 * then executed: <ol>
 * <li>It is verified that the allocation counter in the dummy
 * telecommand loader is equal to 3.</li>
 * <li>It is verified that the telecommand manager reports: "three
 * pending telecommands".</li>
 * <li>The telecommand manager is activated and it is verified that
 * the third telecommand (time tag equal to 0) is executed.</li>
 * <li>It is verified that the telecommand manager reports: "two
 * pending telecommands".</li>
 * <li>It is verified that an event was created to record the
 * unloading of the telecommand.</li>
 * <li>The telecommand manager is repeatedly activated until the time
 * tag of the first telecommand is reached and it is verified
 * that the telecommand is executed.</li>
 * <li>It is verified that the telecommand manager reports: "one
 * pending telecommand".</li>
 * <li>The telecommand manager is repeatedly activated until the time
 * tag of the last remaining telecommand is reached and it is verified
 * that the telecommand is executed.</li>
 * <li>It is verified that the telecommand manager reports: "no
 * pending telecommands".</li>
 * <li>It is verified that the allocation counter in the dummy
 * telecommand loader has gone back to 0.</li>
 * </ol>
 * @see CC_TelecommandManager
 * @see DC_DummyTelecommand
 * @see DC_DummyTelecommandLoader
 * @author Alessandro Pasetti (P&P Software GmbH)
 * @version 1.0
 */
class TestCaseTelecommandManager_2 : public TestCaseGenericSetUp {

public :

     /**
      * Set the identifier and the name of the test case to, respectively,
      * ID_TELECOMMANDMANAGER*10+2 and "TestCaseTelecommandManager_2".
      */
     TestCaseTelecommandManager_2(void);

     /**
      * Execute the test case. See class comment for details.
      */
     virtual void runTestCase(void);
};

#endif
