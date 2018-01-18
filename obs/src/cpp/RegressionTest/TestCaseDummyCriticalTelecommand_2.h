//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseDummyCriticalTelecommand_2.h
//
// Version	1.0
// Date		17.06.03
// Author	R. Totaro

#ifndef TestCaseDummyCriticalTelecommand_2H
#define TestCaseDummyCriticalTelecommand_2H

#include "../Utilities/TestCaseWithEvtCheck.h"

/**
 * Check selected functionalities of critical telecommands. The check
 * is performed on an instance of class <code>DC_DummyCriticalTelecommand</code>.
 * The following functionalities are checked:<ol>
 * <li><code>canExecute()</code></li>
 * <li><code>doAction()</code></li>
 * <li><code>reset()</code></li>
 * <li><code>doCriticalAction()</code></li>
 * <li><code>getNumberOfExecutions()</code></li>
 * </ol>
 * An instance of the <code>DC_DummyCriticalTelecommand</code> class is created
 * and the following tests are performed:<ol>
 * <li>The object is initialized and its criticality level set to NOT_CRITICAL.
 * It is verified that <code>canExecute()</code> returns true.</li>
 * <li><code>execute()</code> is called and it is verified that it returns
 * <code>ACTION_SUCCESS</code> and that <code>doCriticalAction()</code> is called.</li>
 * <li>The TC criticality level is set to CRITICAL, <code>canExecute()</code> is called
 * and it is verified that it returns true.</li>
 * <li><code>execute()</code> is invoked and it is verified that it returns
 * <code>ACTION_SUCCESS</code>, that the TC is armed, that <code>timeWhenArmed</code> is
 * set to the current time and that an <code>EVT_CRIT_TC_ARMED</code> event is added
 * to the repository.</li>
 * <li><code>canExecute()</code> is invoced once again. This time it shall fail and add an
 * <code>EVT_CRIT_TC_IMG_INV</code> event to the repository (the TC image is not valid). The
 * TC shall still be armed.</li>
 * <li><code>reset()</code> is called and it is verified that all the state variables are
 * set to their initial values. <code>pObsClock</code> can not be accessed, however.</li>
 * <li>The TC is re-initialized, re-armed (by calling <code>execute</code>) and the image
 * validity flag is set to true. A this point it is verified that <code>canExecute()</code>
 * returns true.</li>
 * <li><code>execute()</code> is invoked and it is verified that <code>numberOfExecutions</code>
 * is incremented (meaning that <code>doCriticalAction</code> was invoked). It is also
 * verified that the TC is no longer armed and that the "time when armed" is set to an
 * invalid value.</li>
 * <li>The TC is reset, initialized and re-armed. The image validity is set to true and the
 * OBS clock is advanced to the end of the TC's armed duration interval. It is then
 * verified that a call to <code>canExecute()</code> returns false and that an event of type
 * <code>EVT_CRIT_TC_TIMEOUT</code> is added to the repository.</li>
 * <li>The previous step is repeated with the only difference that now the image validity
 * flag is set to false.</li>
 * </ol>
 * @see DC_DummyCriticalTelecommand
 * @see TestCaseDummyCriticalTelecommand_1
 * @author Roberto Totaro
 * @version 1.0
 */
class TestCaseDummyCriticalTelecommand_2 : public TestCaseWithEvtCheck {
public:
	/**
	 * Set the identifier and the name of the test case to, respectively,
	 * ID_DUMMYCRITICALTELECOMMAND*10+2 and "TestCaseDummyCriticalTelecommand_2".
	 */
	TestCaseDummyCriticalTelecommand_2(void);

	/**
	 * Execute the test case. See class comment for details.
	 */
	virtual void runTestCase(void);
};

#endif
