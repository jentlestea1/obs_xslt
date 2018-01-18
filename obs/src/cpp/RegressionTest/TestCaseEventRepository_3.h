//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseEventRepository_3.h
//
// Version	1.0
// Date		15.10.02
// Author	A. Pasetti (P&P Software)

#ifndef TestCaseEventRepository_3H
#define TestCaseEventRepository_3H

#include "../Utilities/TestCaseGenericSetUp.h"

/**
 * Verify the enable and disable services of the
 * <code>DC_EventRepository</code> class.
 * One instance of the class is created and the following specific tests are
 * performed upon it: <ol>
 * <li>The enable status of the repository is changed to "disabled" and it
 * it is verified that the change is correctly reported.</li>
 * <li>An "event create" request is sent to the disabled repository and it is checked that
 * the event counter and the latest event in the repository are not
 * changed (which indicates that no event was created in the repository).</li>
 * <li>The enable status of the repository is changed back to "enabled" and it
 * it is verified that "event create" requests are correctly executed and
 * results in the creation of a new event in the repository.</li>
 * <li>A "selective disable request" is made to disable collection of event reports of
 * a specific type and it is verified that the change in enable status is correctly
 * reported.</li>
 * <li>An "event create" request is sent to the repository
 * for an event of the disabled type and it
 * is checked that the event counter does not
 * change (which indicates that no event was created in the repository).</li>
 * <li>An "event create" request is sent to the repository
 * for an event that is still enabled and it
 * is checked that the event counter is incremented by 1
 * (which indicates that no event was created in the repository).</li>
 * </ol>
 * @see DC_EventRepository
 * @author Alessandro Pasetti (P&P Software GmbH)
 * @version 1.0
 */
class TestCaseEventRepository_3 : public TestCaseGenericSetUp {

public :

     /**
      * Set the identifier and the name of the test case to, respectively,
      * ID_EVENTREPOSITORY*10+3 and "TestCaseEventRepository_3".
      */
     TestCaseEventRepository_3(void);

     /**
      * Execute the test case. See class comment for details.
      */
	virtual void runTestCase(void);
};

#endif
