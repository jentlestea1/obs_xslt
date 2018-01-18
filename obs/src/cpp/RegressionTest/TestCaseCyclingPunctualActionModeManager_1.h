//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseCyclingPunctualActionModeManager_1.h
//
// Version	1.0
// Date		24.02.03
// Author	A. Pasetti (P&P Software)

#ifndef TestCaseCyclingPunctualActionModeManager_1H
#define TestCaseCyclingPunctualActionModeManager_1H

#include "../Utilities/TestCaseWithEvtCheck.h"

/**
 * Verify the services implemented
 * by class <code>CyclingPunctualActionModeManager</code>.
 * For the test, the mode manager is configured as follows:
 * <ul>
 * <li>The number of modes (and hence the number of lists) is 3</li>
 * <li>The length of the three lists associated to the three
 * modes is as follows: 3, 2, 3</li>
 * <li>The items loaded in the the lists are instances of class
 * <code>DC_DummyPunctualAction</code></li>
 * </ul>
 * The following specific checks are performed on the list mode manager:<ol>
 * <li>The correctness of the class identifier is verified.</li>
 * <li>It is verified that the mode manager is not configured at
 * creation.</li>
 * <li>The mode manager is configured as described above and
 * it is verified that the configuration check service reports:
 * "object configured".</li>
 * <li>An iteration through the items in the current list
 * is performed and it is verified that the items in the list
 * are returned without error and in the correct sequence.</li>
 * <li>A (non-nominal) call to method <code>nextInt</code> is performed
 * after the iteration has terminated and it is verified that the
 * last item in the iteration list is returned.</li>
 * <li>A new iteration is performed. While the iteration is under
 * way, an update request is performed and it is verified
 * that this has no effect on the continuation of the iteration.</li>
 * <li>Non-nominal behaviour check: an attempt is made to reconfigure the
 * list by loading an item at a non-existent location and it is checked that
 * the correct event is generated.</li>
 * </ol>
 * @see DC_CyclingPunctualActionModeManager
 * @author Alessandro Pasetti (P&P Software GmbH)
 * @version 1.0
 */
class TestCaseCyclingPunctualActionModeManager_1 : public TestCaseWithEvtCheck {

public :

     /**
      * Set the identifier and the name of the test case to, respectively,
      * ID_CYCLINGPUNCTUALACTIONMODEMANAGER*10+1 and "TestCaseCyclingPunctualActionModeManager_1".
      */
     TestCaseCyclingPunctualActionModeManager_1(void);

     /**
      * Execute the test case. See class comment for details.
      */
	virtual void runTestCase(void);
};

#endif
