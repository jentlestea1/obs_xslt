//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseManoeuvreManager_3.h
//
// Version	1.0
// Date		31.08.03 (Version 1.0)
// Author	A. Pasetti

#ifndef TestCaseManoeuvreManager_3H
#define TestCaseManoeuvreManager_3H

#include "../Utilities/TestCaseWithEvtCheck.h"

/**
 * Verify the suspend/resume operations on manoeuvres and the use of the activation
 * step counter.
 * One instance of the <code>DC_DummyConfigurableManoeuvre</code> class is created and loaded
 * in a manoeuvre manager. The following operations are then performed: <ol>
 * <li>The <code>startCheck</code>
 * and <code>continuationCheck</code> flags of the manoeuvre are set to <code>true</code>.
 * The <code>terminationCheck</code> of the manoeuvre is set to <code>false</code>.</li>
 * <li>It is verified that the initial value of the activation step counter is equal
 * to zero.</li>
 * <li><code>activate()</code> is invoked twice and it is verified that the continuation
 * action counter of the manoeuvre is incremented twice.</li>
 * <li>It is verified that the activation step counter now has value 2.</li>
 * <li>The manoeuvre is suspended (its isSuspended flag is set to true), the manoeuvre
 * manager is activated and it is verified that the continuation counter is not incremented.</li>
 * <li>It is verified that the activation step counter has not been incremented.</li>
 * <li>The <code>terminationCheck</code> of the manoeuvre is set to <code>true</code>, the
 * manoeuvre manager is activated (thus causing the manoeuvre to be terminated and
 * unloaded) and it is verified that the manoeuvre status is
 * "not suspended".<li>
 * <li>The manoeuvre is reloaded, it is suspended and then manoeuvre manager is
 * activated. It is verified that the activation step counter has been reset to zero.<li>
 * <li>The manoeuvre is aborted. It is verified
 * that the manoeuvre status is changed to "not suspended".<li>
 * <li><li>
 * </ol>
 * @see CC_ManoeuvreManager
 * @see DC_DummyConfigurableManoeuvre
 * @see Manoeuvre#setIsSuspended
 * @author A. Pasetti
 * @version 1.0
 */
class TestCaseManoeuvreManager_3 : public TestCaseWithEvtCheck {

  public:
	/**
	 * Set the identifier and the name of the test case to, respectively,
	 * ID_MANOEUVREMANAGER*10+3 and "TestCaseManoeuvreManager_3".
	 */
	TestCaseManoeuvreManager_3(void);

	/**
	 * Execute the test case. See class comment for details.
	 */
	virtual void runTestCase(void);
};

#endif
