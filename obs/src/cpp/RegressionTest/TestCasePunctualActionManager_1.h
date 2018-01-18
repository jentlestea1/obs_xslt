//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCasePunctualActionManager_1.h
//
// Version	1.0
// Date		30.09.03
// Author	R. Totaro

#ifndef TestCasePunctualActionManager_1H
#define TestCasePunctualActionManager_1H

#include "../Utilities/TestCaseGenericSetUp.h"

/**
 * Verify the services offered by the punctual action manager as implemented
 * by the <code>CC_PunctualActionManager</code> class.
 * An instance of this class is created and the following tests are performed:<ol>
 * <li>The correctness of the class id is verified.</li>
 * <li>It is verified that the newly created object is not configured and that
 * <code>getPunctualActionModeManager()</code> returns a null pointer.</li>
 * <li>The <code>setPunctualActionModeManager()</code> is invoked with a pointer
 * to a properly configured <code>PunctualActionModeManager</code> object. It is
 * verified that <code>getPunctualActionModeManager()</code> returns the correct
 * pointer and that the object is configured.</li>
 * <li>The <code>activate()</code> method is invoked twice and it is verified that
 * the activation counters of the <code>DC_DummyPunctualAction</code> objects in the
 * mode manager list are equal to two.</li>
 * </ol>
 * @see CC_PunctualActionManager
 * @see DC_DummyPunctualAction
 * @see DC_SimplePunctualActionModeManager
 * @author Roberto Totaro
 * @version 1.0
 */
class TestCasePunctualActionManager_1 : public TestCaseGenericSetUp {
public:
	/**
	 * Set the identifier and the name of the test case to, respectively,
	 * ID_PUNCTUALACTIONMANAGER*10+1 and "TestCasePunctualActionManager_1".
	 */
	TestCasePunctualActionManager_1(void);

	/**
	 * Execute the test case. See class comment for details.
	 */
	virtual void runTestCase(void);
};

#endif
