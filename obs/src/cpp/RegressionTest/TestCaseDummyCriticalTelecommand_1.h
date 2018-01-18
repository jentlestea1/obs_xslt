//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseDummyCriticalTelecommand_1.h
//
// Version	1.0
// Date		17.06.03
// Author	R. Totaro

#ifndef TestCaseDummyCriticalTelecommand_1H
#define TestCaseDummyCriticalTelecommand_1H

#include "../Utilities/TestCaseGenericSetUp.h"

/**
 * Verify the basic services offered by critical telecommands as implemented
 * by the <code>DC_DummyCriticalTelecommand</code> class. The <code>canExecute()</code>,
 * <code>doAction()</code> and <code>reset()</code> methods are tested by
 * <code>TestCaseDummyCriticalTelecommand_2</code>. An instance of this class is created
 * and the following tests are performed:<ol>
 * <li>The correctness of the class identifier is verified.</li>
 * <li>The Telecommand class (CriticalTelecommand's base class) is
 * configured by invoking <code>setTimeTag()</code>. It
 * is verified that the <code>DC_DummyCriticalTelecommand</code> class is not yet fully
 * configured.</li>
 * <li><code>setMaxArmedDuration()</code> is called. It is verified that the class is not
 * yet configured and that <code>getMaxArmedDuration</code> returns the correct value.</li>
 * <li>An <code>DC_DummyObsClock</code> object is created and it is attached to the critical
 * telecommand by calling <code>setObsClock()</code>. It is verified that the object is finally
 * configured and that <code>getObsClock()</code> returns the correct value.</li>
 * <li>It is verified that the newly created telecommand is critical and not armed.</li>
 * <li>It is verified that the criticality level can be modified.</li>
 * <li>It is verified that the image validity flag can be set and retrieved correctly.</li>
 * <li>Finally, it is verified that the "time when armed" is set to an invalid value.</li>
 * </ol>
 * @see DC_DummyCriticalTelecommand
 * @see TestCaseDummyCriticalTelecommand_2
 * @author Roberto Totaro
 * @version 1.0
 */
class TestCaseDummyCriticalTelecommand_1 : public TestCaseGenericSetUp {
public:
	/**
	 * Set the identifier and the name of the test case to, respectively,
	 * ID_DUMMYCRITICALTELECOMMAND*10+1 and "TestCaseDummyCriticalTelecommand_1".
	 */
	TestCaseDummyCriticalTelecommand_1(void);

	/**
	 * Execute the test case. See class comment for details.
	 */
	virtual void runTestCase(void);
};

#endif
