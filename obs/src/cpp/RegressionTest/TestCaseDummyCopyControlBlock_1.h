//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseDummyCopyControlBlock_1.h
//
// Version	1.3
// Date		22.05.03 (Version 1.0)
//          14.10.03 (Version 1.1)
//          16.10.03 (Version 1.2 & 1.3)
// Author	R. Totaro, A. Pasetti
//
// Change Record:
//   Version 1.1: Updated to reflect the new structure of the ControlBlock class
//   Version 1.2: Test case renamed (from TestCaseDummyControlBlock_1H
//                to TestCaseDummyCopyControlBlock_1)
//   Version 1.2: Amended the test description

#ifndef TestCaseDummyCopyControlBlock_1H
#define TestCaseDummyCopyControlBlock_1H

#include "../Utilities/TestCaseWithEvtCheck.h"

/**
 * Check the services implemented by the <code>CopyControlBlock</code> class.
 * Since this class is abstract, the check is performed upon
 * its concrete subclass <code>DC_DummyCopyControlBlock</code>. One instance
 * of this class is created and the following checks are performed upon it: <ol>
 * <li>The correctness of the class identifier is verified.</li>
 * <li>It is verified that the control block is configured at creation.</li>
 * <li>The number of states, inputs, outputs and parameters is read
 * with the getter methods and it is checked that their values are correct.</li>
 * <li>It is verified that the initial values of the state and inputs are correctly set.</li>
 * <li>The parameter values are set and the correctness of their values is checked.</li>
 * <li>The input values are set and <code>propagate()</code> is invoked. It is
 * verified that both state and outputs are properly updated.</li>
 * <li>The output values are set and the correctness of their values is checked.</li>
 * <li>The state values are set and the correctness of their values is checked.</li>
 * <li>Non-nominal behaviour check: an attempt is made to set a state value with an illegal state index and it is
 * checked that the correct event is generated.</li>
 * <li>Non-nominal behaviour check: an  attempt is made to set an output value with an illegal output index and it is
 * checked that the correct event is generated.</li>
 * <li>Non-nominal behaviour check: an  attempt is made to set an input value with an illegal input index and it is
 * checked that the correct event is generated.</li>
 * <li>Non-nominal behaviour check: an  attempt is made to set a parameter value with an illegal parameter index and it is
 * checked that the correct event is generated.</li>
 * <li>The <code>reset()</code> method is invoked and it is verified that the
 * states and inputs are reset to their default values.</li>
 * </ol>
 * @see DC_DummyCopyControlBlock
 * @see CopyControlBlock
 * @author Roberto Totaro, Alessandro Pasetti
 * @version 1.2
 */
class TestCaseDummyCopyControlBlock_1 : public TestCaseWithEvtCheck {
public:
	/**
	 * Set the identifier and the name of the test case to, respectively,
	 * ID_DUMMYCOPYCONTROLBLOCK*10+1 and "TestCaseDummyCopyControlBlock_1".
	 */
	TestCaseDummyCopyControlBlock_1(void);

	/**
	 * Execute the test case. See class comment for details.
	 */
	virtual void runTestCase(void);
};
#endif
