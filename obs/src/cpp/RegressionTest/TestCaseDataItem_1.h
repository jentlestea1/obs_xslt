//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseDataItem_1.h
//
// Version	2.0
// Date		17.04.03 (Version 1.1)
//          11.06.03 (Version 2.0)
// Author	R. Totaro
//
// Change Record:
//   Version 2.0: Changed the test description.

#ifndef TestCaseDataItem_1H
#define TestCaseDataItem_1H

#include "../Utilities/TestCaseGenericSetUp.h"

/**
 * Check the data set and get services for class <code>DC_DataItem</code>.
 * Two <code>DC_DataItem</code> objects are created to encapsulate access to,
 * respectively, a <code>TD_Float</code> and <code>TD_Integer</code> variable.
 * The following specific checks are performed:
 * <ol>
 * <li>The values of the encapsulated variables are set and then read back
 * through the data item accessor methods and it is checked that the read-back value
 * is correct.</li>
 * <li>The values of the data item are set through the data item accessor methods
 * and then read back and it is checked that the read-back value
 * is correct.</li>
 * </ol>
 * @author Roberto Totaro
 * @version 1.0
 */
class TestCaseDataItem_1 : public TestCaseGenericSetUp {
public :
	/**
	 * Set the identifier and the name of the test case to, respectively,
	 * ID_DATAITEM*10+1 and "TestCaseDataItem_1".
	 */
	TestCaseDataItem_1(void);

	/**
	 * Execute the test case. See class comment for details.
	 */
	virtual void runTestCase(void);
};

#endif
