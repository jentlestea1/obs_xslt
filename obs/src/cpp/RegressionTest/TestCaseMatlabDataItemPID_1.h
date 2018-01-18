//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseMatlabDataItemPID_1.h
//
// Version	1.0
// Date		29.10.03 (Version 1.0)
// Author	R. Totaro

#ifndef TestCaseMatlabDataItemPID_1H
#define TestCaseMatlabDataItemPID_1H

#include "../Utilities/TestCaseGenericSetUp.h"

/**
 * Verify the services implemented by the <code>DC_MatlabDataItemPID</code> class.
 * One instance of this class and two <code>DC_DataItem</code> objects are created
 * and the following tests are performed: <ol>
 * <li>The correctness of the class identifier is verified.</li>
 * <li>It is verified that the control block is not configured at creation.</li>
 * <li>The input data item is linked to the control block and it is checked that
 * the control block is not yet configured.</li>
 * <li>The output data item is linked tp the control block and it is checked that
 * the control block is now configured.</li>
 * <li>It is verified that the number of parameters returned by
 * <code>getNumberOfParameters</code> is correct.</li>
 * </ol>
 * This and the following steps are performed only if the pre-processor symbol
 * <code>HAVE_SIMULINK</code> is defined:
 * <ol>
 * <li>The control block's parameters are initialized.</li>
 * <li>The input is set to 1.0 and <code>propagate()</code> is invoked twice. After
 * each call it is verified that the output is properly updated.</li>
 * <li>The <code>reset()</code> method is invoked and it is verified that the
 * state is reverted to the default value. The state of the Simulink model can not be
 * accessed, therefore this check is performed by examining the output value after
 * calling <code>propagate()</code>.</li>
 * <li><code>reset()</code> is called, the <code>Kp</code> parameter is set to 0.0 and
 * <code>propagate</code> is invoked twice. It is verified that the output reflects the
 * change in the parameter value.</li>
 * </ol>
 * The use of the preprocessor symbol <code>HAVE_SIMULINK</code> violates project-specific
 * coding rule PR9.2. This is necessary to allow construction of the regression test for
 * users who do not have access to the Matlab/simulink suite.
 * <p/>
 * Simulink is a trademark of The Mathworks, Inc.
 *
 * @see DC_MatlabDataItemPID
 * @author Roberto Totaro
 * @version 1.0
 */
class TestCaseMatlabDataItemPID_1 : public TestCaseGenericSetUp {
public:
     /**
      * Set the identifier and the name of the test case to, respectively,
      * ID_MATLABDATAITEMPID*10+1 and "TestCaseMatlabDataItemPID_1".
      */
     TestCaseMatlabDataItemPID_1(void);

     /**
      * Execute the test case. See class comment for details.
      */
	virtual void runTestCase(void);
};
#endif
