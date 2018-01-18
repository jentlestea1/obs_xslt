//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseDummyDataItemControlBlock_1.h
//
// Version	1.0
// Date		30.10.03 (Version 1.0)
// Author	R. Totaro
//
// Change Record:

#ifndef TestCaseDummyDataItemControlBlock_1H
#define TestCaseDummyDataItemControlBlock_1H

#include "../Utilities/TestCaseWithEvtCheck.h"

/**
 * Check the services implemented by the <code>DataItemControlBlock</code> class.
 * Since this class is abstract, the check is performed upon
 * its concrete subclass <code>DC_DummyDataItemControlBlock</code>. One instance
 * of this class is created and the following checks are performed upon it:<ol>
 * <li>The correctness of the class identifier is verified.</li>
 * <li>The number of states, inputs, outputs and parameters read
 * with the getter methods and it is checked that their values are correct.</li>
 * <li>The control block's inputs and outputs are linked to previously created
 * <code>DC_DataItem</code> objects and it is verified that the control block
 * is configured only when all inputs and outputs are linked.</li>
 * <li><code>reset()</code> is called and it is verified that the initial values of
 * the state variables are correctly set.</li>
 * <li>The parameter values are set and the correctness of their values is checked.</li>
 * <li>The input values are set and <code>propagate()</code> is invoked. It is
 * verified that both state and outputs are properly updated.</li>
 * <li>The state values are set and the correctness of their values is checked.</li>
 * </ol>
 * The following tests are performed only if the non nominal checks are allowed:
 * <ol>
 * <li>An attempt is made to link an input with an illegal index and it is
 * checked that the correct event is generated.</li>
 * <li>An attempt is made to link an output with an illegal index and it is
 * checked that the correct event is generated.</li>
 * <li>An attempt is made to set a state value with an illegal index and it is
 * checked that the correct event is generated.</li>
 * <li>An attempt is made to set a parameter value with an illegal index and
 * it is  checked that the correct event is generated.</li>
 * </ol>
 * @see DC_DummyDataItemControlBlock
 * @see DataItemControlBlock
 * @author Roberto Totaro
 * @version 1.0
 */
class TestCaseDummyDataItemControlBlock_1 : public TestCaseWithEvtCheck {
public:
	/**
	 * Set the identifier and the name of the test case to, respectively,
	 * ID_DUMMYDATAITEMCONTROLBLOCK*10+1 and "TestCaseDummyDataItemControlBlock_1".
	 */
	TestCaseDummyDataItemControlBlock_1(void);

	/**
	 * Execute the test case. See class comment for details.
	 */
	virtual void runTestCase(void);
};
#endif
