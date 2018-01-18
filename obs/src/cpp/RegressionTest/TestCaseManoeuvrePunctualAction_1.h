//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseManoeuvrePunctualAction_1.h
//
// Version	1.0
// Date		06.06.03 (Version 1.0)
// Author	R. Totaro

#ifndef TestCaseManoeuvrePunctualAction_1H
#define TestCaseManoeuvrePunctualAction_1H

#include "../Utilities/TestCaseGenericSetUp.h"

/**
 * Verify the functionality implemented  by the <code>DC_ManoeuvrePunctualActionr</code>
 * class. An instance of this class is created and the following tests
 * are performed upon it: <ol>
 * <li>The correctness of the class identifier is verified.</li>
 * <li>It is verified that the action is not configured at creation.</li>
 * <li>A previously created and configured <code>CC_ManoeuvreManager</code> is
 * attached to the action. It is verified that the manoeuvre manager pointer
 * can be retrieved by calling <code>getManoeuvreManager</code> and that the
 * action is not yet configured.</li>
 * <li>A previously created <code>DC_DummyManoeuvre</code> is attached to the
 * action. It is verified that the manoeuvre pointer can be retrieved by calling
 * <code>getManoeuvre</code> and that the action is now fully configured.</li>
 * <li>The inherited method <code>execute()</code> is invoked and it is verified
 * that the manoeuvre is loaded into the manoeuvre manager.</li>
 * </ol>
 * @see DC_ManoeuvrePunctualAction
 * @see PunctualAction
 * @see CC_ManoeuvreManager
 * @see Manoeuvre
 * @see DC_DummyManouvre
 * @author Roberto Totaro
 * @version 1.0
 */
class TestCaseManoeuvrePunctualAction_1 : public TestCaseGenericSetUp {

  public:
	/**
	 * Set the identifier and the name of the test case to, respectively,
	 * ID_MANOEUVREPUNCTUALACTION*10+1 and "TestCaseManoeuvrePunctualAction_1".
	 */
	TestCaseManoeuvrePunctualAction_1(void);

	/**
	 * Execute the test case. See class comment for details.
	 */
	virtual void runTestCase(void);
};
#endif
