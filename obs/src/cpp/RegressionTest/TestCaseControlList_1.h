//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseControlList_1.h
//
// Version	1.0
// Date		11.10.03 (Version 1.0)
// Author	R. Totaro
//
// Change Record:

#ifndef TestCaseControlList_1H
#define TestCaseControlList_1H

#include "../Utilities/TestCaseWithEvtCheck.h"

/**
 * Verify the <code>DC_ControlList</code> class.
 * An instance of this class is created and the following  tests are
 * performed on it:<ol>
 * <li>The correctness of the class identifier is verified.</li>
 * <li>It is verified that the newly created object is not configured.</li>
 * <li>The control block list size is set. It is then verified that
 * <code>getListSize()</code> returns the correct value.</li>
 * <li>A number of pre-configured control blocks is loaded and it is verified that
 * <code>getControlBlock()</code> returns the correct values.</li>
 * <li>During the loading of the control blocks, it is verified that the object
 * stays in the unconfigured status until the last control block is loaded.</li>
 * <li>Non-nominal behaviour check: it is verified that an invocation of <code>setControlBlock()</code> with
 * an illegal index generates an error report.</li>
 * <li>The <code>execute()</code> method is invoked. It is verified that the return
 * code is <code>ACTION_SUCCESS</code> and that the <code>propagate()</code> method
 * of all the loaded control blocks is invoked.</li>
 * <li><code>reset()</code> is called and it is verified that the status of all
 * the loaded control blocks is reset to its default value.</li>
 * </ol>
 * @see DC_ControlList
 * @see DC_DummyControlBlock
 * @author Roberto Totaro
 * @version 1.0
 */
class TestCaseControlList_1 : public TestCaseWithEvtCheck {
public:
	/**
	 * Set the identifier and the name of the test case to, respectively,
	 * ID_CONTROLLIST*10+1 and "TestCaseControlList_1".
	 */
	TestCaseControlList_1(void);

	/**
	 * Execute the test case. See class comment for details.
	 */
	virtual void runTestCase(void);
};
#endif
