//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseEventRepository_2.h
//
// Version	1.0
// Date		15.09.02
// Author	     A. Pasetti (P&P Software)

#ifndef TestCaseEventRepository_2H
#define TestCaseEventRepository_2H

#include "../Utilities/TestCaseGenericSetUp.h"

/**
 * Verify the event creation and retrieval service of class
 * <code>DC_EventRepository</code>.
 * The following specific tests are performed: <ol>
 * <li>Two events are created in a configured event repository and it is
 * verified that the event counter is incremented by two. </li>
 * <li>The iteration service of the event repository is used to retrieve the
 * events in the repository and it is checked that the correct events are retrieved.</li>
 * <li>More events are added to the event repository until one is overwritten after
 * the repository size is exceeded and it is checked that the event counter has the
 * correct value and that the iterator performs as expected.</li>
 * <li>It is verified that <code>reset()</code> does not clear the event counter.</li>
 * </ol>
 * @see DC_EventRepository
 * @author Alessandro Pasetti (P&P Software GmbH)
 * @version 1.0
 */
class TestCaseEventRepository_2 : public TestCaseGenericSetUp {

public :

     /**
      * Set the identifier and the name of the test case to, respectively,
      * ID_EVENTREPOSITORY*10+2 and "TestCaseEventRepository_2".
      */
     TestCaseEventRepository_2(void);

     /**
      * Execute the test case. See class comment for details.
      */
	virtual void runTestCase(void);
};

#endif
