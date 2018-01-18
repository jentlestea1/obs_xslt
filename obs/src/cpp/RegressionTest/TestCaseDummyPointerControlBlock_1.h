//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseDummyPointerControlBlock_1.h
//
// Version	1.0
// Date		16.10.03 (Version 1.0)
// Author	R. Totaro
//
// Change Record:

#ifndef TestCaseDummyPointerControlBlock_1H
#define TestCaseDummyPointerControlBlock_1H

#include "../Utilities/TestCaseWithEvtCheck.h"

/**
 * Check the services implemented by the <code>PointerControlBlock</code> class.
 * Since this class is abstract, the check is performed upon
 * its concrete subclass <code>DC_DummyPointerControlBlock</code>. One instance
 * of this class is created and the following checks are performed upon it: <ol>
 * <li>The correctness of the class identifier is verified.</li>
 * <li>The number of states, inputs, outputs and parameters read
 * with the getter methods and it is checked that their values are correct.</li>
 * <li>The input and output variables are linked to the control block and it is
 * verified that the object is configured only when all the variables are linked.</li>
 * <li><code>reset()</code> is called and it is verified that the initial values of
 * the state variables are correctly set.</li>
 * <li>The parameter values are set and the correctness of their values is checked.</li>
 * <li>The input values are set and <code>propagate()</code> is invoked. It is
 * verified that both state and outputs are properly updated.</li>
 * <li>The state values are set and the correctness of their values is checked.</li>
 * <li>Non-nominal behaviour check: an attempt is made to set a state value with an illegal state index and it is
 * checked that the correct event is generated.</li>
 * <li>Non-nominal behaviour check: an attempt is made to set a parameter value with an illegal parameter index and it is
 * checked that the correct event is generated.</li>
 * </ol>
 * @see DC_DummyPointerControlBlock
 * @see PointerControlBlock
 * @author Roberto Totaro
 * @version 1.0
 */
class TestCaseDummyPointerControlBlock_1 : public TestCaseWithEvtCheck {
public:
	/**
	 * Set the identifier and the name of the test case to, respectively,
	 * ID_DUMMYPOINTERCONTROLBLOCK*10+1 and "TestCaseDummyPointerControlBlock_1".
	 */
	TestCaseDummyPointerControlBlock_1(void);

	/**
	 * Execute the test case. See class comment for details.
	 */
	virtual void runTestCase(void);
};
#endif
