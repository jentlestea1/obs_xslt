//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseManoeuvreManager_1.h
//
// Version	1.0
// Date		08.05.03 (Version 1.0)
// Author	R. Totaro

#ifndef TestCaseManoeuvreManager_1H
#define TestCaseManoeuvreManager_1H

#include "../Utilities/TestCaseWithEvtCheck.h"

/**
 * Verify the services implemented by the <code>CC_ManoeuvreManager</code> class.
 * All the services are tested, apart from the <code>activate</code> method.
 * One instance of the class is created and the following tests are performed: <ol>
 * <li>The correctness of the class identified is verified.</li>
 * <li>It is verified that the manoeuvre manager is not configured at creation.</li>
 * <li>The manoeuvre list is allocated and it is verified that its size is properly
 * reported and that the <code>isObjectConfigured</code> return value reflects the
 * change (the object shall now be configured).</li>
 * <li>It is verified that no manoeuvres are pending.</li>
 * <li>A number of <code>DC_DummyManoeuvre</code> objects equal to length of the
 * manoeuvre list is loaded into the manoeuvre manager (the manoeuvre list should
 * now be full). It is verified that <code>manCounter</code> is updated.</li>
 * <li>One of the previously loaded manoeuvre is aborted. It is verified that
 * <code>manCounter</code> is decremented accordingly and that the aborted
 * manoeuvre is no longer in use.</li>
 * <li>An attempt is made to load an already loaded manoeuvre. It is verified that
 * <code>manCounter</code> is not modified and that a <code>EVT_MAN_ALREADY_IN_USE</code>
 * event is reported.</li>
 * <li>The previously aborted manoeuvre is re-loaded (the manoeuvre list is therefore
 * once again full). An attempt is made to load an additional manoeuvre. It is verified that a
 * <code>EVT_MAN_LIST_FULL</code> event is reported.</li>
 * <li>The manoeuvre manager is reset and it is verified that all the manoeuvres
 * have been aborted (they shall no longer be in use).</li>
 * </ol>
 * @see CC_ManoeuvreManager
 * @see DC_DummyManoeuvre
 * @see TestCaseManoeuvreManager_2
 * @author Roberto Totaro
 * @version 1.0
 */
class TestCaseManoeuvreManager_1 : public TestCaseWithEvtCheck {

  public:
	/**
	 * Set the identifier and the name of the test case to, respectively,
	 * ID_MANOEUVREMANAGER*10+1 and "TestCaseManoeuvreManager_1".
	 */
	TestCaseManoeuvreManager_1(void);

	/**
	 * Execute the test case. See class comment for details.
	 */
	virtual void runTestCase(void);
};
#endif
