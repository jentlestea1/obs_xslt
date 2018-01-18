//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseTelecommandManager_3.h
//
// Version	1.0
// Date		11.12.02
// Author	A. Pasetti (P&P Software)

#ifndef TestCaseTelecommandManager_3H
#define TestCaseTelecommandManager_3H

#include "../Utilities/TestCaseGenericSetUp.h"

/**
 * Check the non-nominal telecommand execution implemented by the
 * telecommand manager.
 * The test uses an instance of class <code>DC_DummyTelecommandLoader</code>
 * as a telecommand loader and three instances of class
 * <code>DC_DummyTelecommand</code> as dummy telecommands.
 * All the telecommands have a time tag equal to zero (immediate execution).
 * The first telecommand is configured to have an execution check that
 * returns "cannot be executed".
 * The second telecommand is configured to have a validity check that
 * returns "telecommand not valid".
 * The telecommand manager is configured with a pending telecommand
 * list size of 2. The test begins by activating the telecommand loader
 * twice to force it to attempt to load the first two dummy telecommands
 * into the telecommand manager. The following specific tests are
 * then executed: <ol>
 * <li>It is verified that the telecommand manager rejects the second
 * telecommand because it fails its validity check.</li>
 * <li>The telecommand loader is activated two more times and it is
 * verified that the telecommand manager rejects the last load attempt
 * because its pending telecommand list is full.</li>
 * <li>The telecommand manager is activated and it is verified that
 * the first telecommand is unloaded without being executed because
 * its execution check fails.</li>
 * <li>It is checked that the allocation counter in the dummy telecommand
 * loader is back to zero.</li>
 * <li>It is verified that the second telecommand is executed.</li>
 * <li>The telecommands loader is activated three times and it is verified
 * that two telecommands are loaded in the telecommand manager (the second
 * one is rejected because it fails its validity check).</li>
 * <li>The telecommands manager is reset and it is verified that the number of
 * pending telecommands goes back to zero.</li>
 * <li>It is verified that two events EVT_TC_ABORTED have been generated
 * as a result of the reset operation.</li>
 * <li>It is checked that the allocation counter in the dummy telecommand
 * loader is back to zero.</li>
 * <li>The telecommands loader is activated three times and it is verified
 * that two telecommands are loaded in the telecommand manager (the second
 * one is rejected because it fails its validity check).</li>
 * <li>An abort request is sent to the first telecommand identified by its
 * identifier. It is verified that only one pending telecommand is left.</li>
 * <li>It is checked that the allocation counter in the dummy telecommand
 * loader is equal to 1.</li>
 * <li>It is checked that one event of type EVT_TC_ABORTED was generated.</li>
 * <li>An abort request is sent to the third telecommand identified by its
 * pointer. It is verified that there are no pending telecommand left.</li>
 * <li>It is checked that the allocation counter in the dummy telecommand
 * loader is back to zero.</li>
 * <li>It is checked that one event of type EVT_TC_ABORTED was generated.</li>
 * </ol>
 * @see CC_TelecommandManager
 * @see DC_DummyTelecommand
 * @see DC_DummyTelecommandLoader
 * @author Alessandro Pasetti (P&P Software GmbH)
 * @version 1.0
 */
class TestCaseTelecommandManager_3 : public TestCaseGenericSetUp {

public :

     /**
      * Set the identifier and the name of the test case to, respectively,
      * ID_TELECOMMANDMANAGER*10+3 and "TestCaseTelecommandManager_3".
      */
     TestCaseTelecommandManager_3(void);

     /**
      * Execute the test case. See class comment for details.
      */
     virtual void runTestCase(void);
};

#endif
