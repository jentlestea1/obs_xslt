//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseFSM_1.h
//
// Version	1.0
// Date		04.10.02
// Author	A. Pasetti (P&P Software)

#ifndef TestCaseFSM_1H
#define TestCaseFSM_1H

#include "../Utilities/TestCaseWithEvtCheck.h"

/**
 * Verify the initialization and configuration of the
 * <code>CC_FSM</code> class. One instance of the class is created
 * and the following tests are performed upon it: <ol>
 * <li>The correctness of the class identifier is verified.</li>
 * <li>It is verified
 * that the object configuration service immediately after object creation
 * reports "object not configured".</li>
 * <li>The number of states is set and it is verified that this is correctly
 * reported.</li>
 * <li>Four dummy FsmStates are loaded into the FSM and it is verified that
 * the load operation is correctly performed.</li>
 * <li>Non-nominal behaviour check: an attempt is made to load a state at an illegal location and it is
 * verified that the correct event is generated. </li>
 * <li>The FSM is reset and it is checked that all state transitions are
 * initialized to "enabled".</li>
 * <li>The correctness of the default state is verified.</li>
 * <li>Non-nominal behviour check: unload one state and check that the object configuration service
 * reports "object not configured" (this check is inserted to ensure full statement coverage of the
 * class under test).</li>
 * <li>Reload the state and check that the object configuration service
 * now reports "object configured".</li>
 * </ol>
 * @see CC_FSM
 * @author Alessandro Pasetti (P&P Software GmbH)
 * @version 1.0
 */
class TestCaseFSM_1 : public TestCaseWithEvtCheck {

public :

     /**
      * Set the identifier and the name of the test case to, respectively,
      * ID_FSM*10+1 and "TestCaseFSM_1".
      */
     TestCaseFSM_1(void);

     /**
      * Execute the test case. See class comment for details.
      */
	virtual void runTestCase(void);
};

#endif
