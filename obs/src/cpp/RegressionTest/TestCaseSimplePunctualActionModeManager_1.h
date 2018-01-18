//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseSimplePunctualActionModeManager_1.h
//
// Version	1.0
// Date		29.09.03
// Author	R. Totaro

#ifndef TestCaseSimplePunctualActionModeManager_1H
#define TestCaseSimplePunctualActionModeManager_1H

#include "../Utilities/TestCaseGenericSetUp.h"

/**
 * Verify the services implemented
 * by class <code>DC_SimplePunctualActionModeManager</code>. An instance of
 * the class is created and
 * the following specific tests are performed upon it:<ol>
 * <li>The correctness of the class identifier is verified.</li>
 * <li>The mode manager is configured and it is verified that it
 * has only one mode and that its default mode index is 0.</li>
 * <li>It is verified that calls to its <code>update</code>
 * method have no effect on the mode.</li>
 * </ol>
 * @see DC_SimplePunctualActionModeManager
 * @author Roberto Totaro
 * @version 1.0
 */
class TestCaseSimplePunctualActionModeManager_1 : public TestCaseGenericSetUp {
public :
    /**
     * Set the identifier and the name of the test case to, respectively,
     * ID_SIMPLEPUNCTUALACTIONMODEMANAGER*10+1 and
     * "TestCaseSimplePunctualActionModeManager_1".
     */
    TestCaseSimplePunctualActionModeManager_1(void);

    /**
     * Execute the test case. See class comment for details.
     */
    virtual void runTestCase(void);
};

#endif
