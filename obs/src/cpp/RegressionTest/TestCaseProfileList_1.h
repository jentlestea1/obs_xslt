//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseProfileList_1.h
//
// Version	1.2
// Date		15.09.03 (Version 1.0)
//          10.10.03 (Version 1.1)
//          21.10.03 (Version 1.2)
// Author	R. Totaro
//
// Change Record:
//   Version 1.1: Amended the test description
//   Version 1.2: Replaced all occurrences of loadMonitoringProfile() with setMonitoringProfile()

#ifndef TestCaseProfileList_1H
#define TestCaseProfileList_1H

#include "../Utilities/TestCaseWithEvtCheck.h"

/**
 * Verify the <code>DC_ProfileList</code> class.
 * An instance of this class is created and the following  tests are
 * performed on it: <ol>
 * <li>The correctness of the class identifier is verified.</li>
 * <li>It is verified that the newly created object is not configured.</li>
 * <li>The profile list size is set. It is then verified that <code>getListSize()</code>
 * returns the correct value.</li>
 * <li>A number of pre-configured monitoring profiles is loaded and it is verified that
 * <code>getMonitoringProfile()</code> returns the correct values.</li>
 * <li>During the loading of the monitoring profiles, it is verified that the object
 * stays in the unconfigured status until the last profile is loaded.</li>
 * <li>Non-nominal behaviour check: it is verified that an invokation of <code>loadMonitoringProfile()</code> with
 * an illegal index generates an error report.</li>
 * <li>The functionality of both implementations of <code>deviatesFromProfile()</code> is
 * verified.</li>
 * </ol>
 * @see DC_ProfileList
 * @see DC_InRangeProfile
 * @author Roberto Totaro
 * @version 1.2
 */
class TestCaseProfileList_1 : public TestCaseWithEvtCheck {
public:
	/**
	 * Set the identifier and the name of the test case to, respectively,
	 * ID_PROFILELIST*10+1 and "TestCaseProfileList_1".
	 */
	TestCaseProfileList_1(void);

	/**
	 * Execute the test case. See class comment for details.
	 */
	virtual void runTestCase(void);
};
#endif
