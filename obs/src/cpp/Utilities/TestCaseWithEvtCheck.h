//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseWithEvtCheck.h
//
// Version	1.0
// Date		28.11.03
// Author	R. Totaro
//
// Change Record:

#ifndef TestCaseWithEvtCheckH
#define TestCaseWithEvtCheckH

#include "../Event/DC_EventRepository.h"
#include "../Utilities/TestCaseGenericSetUp.h"

#define verifyLatestEvent(nEvt,eventType) verifyLatestEventHidden(__LINE__,nEvt,eventType)
#define verifySpecificEvent(n,eventType)  verifySpecificEventHidden(__LINE__,n,eventType)

/**
 * Base class for test cases that need to perform checks on the
 * event repository associated to the <code>CC_RootObject</code>
 * class.
 * Two types of checks are foreseen. The <i>latest event check</i>
 * verifies the type and parameter of the latest event in the
 * repository and the total number of events in the repository.
 * The <i>specific event check</i> verifies the type and parameter
 * of a specific event in the repository.
 * @see CC_RootObject#getEventRepository
 * @author Roberto Totaro
 * @version 1.0
 * @ingroup TestCases
 */
class TestCaseWithEvtCheck : public TestCaseGenericSetUp {

public:
	/**
	 * Set the identifier and the name of the test case.
	 * @param testId the test identifier
	 * @param testName the name of the test
	 */
	TestCaseWithEvtCheck(int testId,char *testName);

	/**
	 * Call the test setup service of the super class.
	 */
	virtual bool setUpTestCase(void);

protected:

	/**
	 * Get the current number of events in the repository.
	 * @return Number of events
	 */
	unsigned int getNumberOfEvents(void) const;

	/**
	 * Get the size of the event repository (the maximum number of events
     * it can contain).
	 * @return Size of event repository
	 */
	unsigned int getEventRepositorySize(void) const;

	/**
	 * Perform a <i>latest event check</i>. More specifically, the
	 * following tests are performed on the event repository associated
	 * to the <code>CC_RootObject</code> class: <ul>
	 * <li>Verifies that the number of events in the repository
	 * is equal to <code>nEvt</code></li>
	 * <li>Checks that the event type of the latest event in the
	 * repository is equal to <code>eventType</code></li>
	 * </ul>
	 * If all the tests are passed, the method returns <code>true</code>,
	 * otherwise <code>false</code>.
	 * @param line line number
	 * @param nEvt the expected number of events in the repository
	 * @param eventType the expected type of the latest event in the repository
	 * @return true if the tests are passed, false otherwise
	 */
	bool verifyLatestEventHidden(const int line,
                                 const unsigned int nEvt,
						         const TD_EventType eventType);

	/**
	 * Perform a <i>specific event check</i>. The event to be checked is the
	 * n-th event in the buffer. The argument n must lie in the range [N-S+1, N]
     * where N is the total number of events stored in the repository since
     * it was created (return value of method <code>getCounter()</code>) and
     * S is the repository size. If the method argument does not satisfy this
     * constraint, the test returns false. Otherwise, the following checks
	 * are performed on the target event: <ul>
	 * <li>Verify that the event type of the checked event in the
	 * repository is equal to <code>eventType</code></li>
	 * </ul>
	 * If all the tests are passed, the method returns <code>true</code>,
	 * otherwise <code>false</code>.
	 * @param line line number
	 * @param n the identifier of the target event
	 * @param eventType the expected type of the target event
	 * @return true if the tests are passed, false otherwise
	 */
	bool verifySpecificEventHidden(const int line,
                                   const unsigned int n,
							       const TD_EventType eventType);
};
#endif
