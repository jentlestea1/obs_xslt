//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseManoeuvreManager_2.h
//
// Version	1.0
// Date		09.05.03 (Version 1.0)
// Author	R. Totaro

#ifndef TestCaseManoeuvreManager_2H
#define TestCaseManoeuvreManager_2H

#include "../Utilities/TestCaseWithEvtCheck.h"

/**
 * Verify the <code>CC_ManoeuvreManager::activate()</code> method.
 * One instance of the class is created and the following operations are performed: <ol>
 * <li>The manoeuvre list is allocated.</li>
 * <li>A number of <code>DC_DummyConfigurableManoeuvre</code> objects equal to length
 * of the manoeuvre list is created.</li>
 * <li> The created manoeuvres are loaded into the manager and their <code>startCheck</code>
 * and <code>continuationCheck</code> flags are set to <code>true</code>.
 * <code>terminationCheck</code> is set to <code>false</code>.</li>
 * <li><code>activate()</code> is invoked once and it is verified that the manoeuvres
 * are intializated and their <code>doContinue()</code> method is called exactly once.</li>
 * <li>The manoeuvres' status is updated according to the <code>manoeuvreStateChange</code>
 * table, then <code>activate()</code> is invoked. It is verified that all the manoeuvres
 * in use are scheduled (i.e. <code>doContinue()</code> is called) and that the manoeuvre
 * manager terminates/aborts and unloads the manoeuvres as expected.</li>
 * <li>The previous step is repeated until no pending manoeuvres are left in the list (nominal
 * case) or a pre-defined maximum number of <code>activate()</code> calls is reached (failure
 * mode).</li>
 * </ol>
 * @see CC_ManoeuvreManager
 * @see DC_DummyConfigurableManoeuvre
 * @see TestCaseManoeuvreManager_1
 * @author Roberto Totaro
 * @version 1.0
 */
class TestCaseManoeuvreManager_2 : public TestCaseWithEvtCheck {

  public:
	/**
	 * Set the identifier and the name of the test case to, respectively,
	 * ID_MANOEUVREMANAGER*10+2 and "TestCaseManoeuvreManager_2".
	 */
	TestCaseManoeuvreManager_2(void);

	/**
	 * Execute the test case. See class comment for details.
	 */
	virtual void runTestCase(void);
};

#endif
