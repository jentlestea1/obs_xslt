//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseRawDataItem_1.h
//
// Version	1.0
// Date		11.10.03 (Version 1.0)
// Author	R. Totaro, A. Pasetti
//
// Change Record:

#ifndef TestCaseRawDataItem_1H
#define TestCaseRawDataItem_1H

#include "../Utilities/TestCaseGenericSetUp.h"

/**
 * Check the setter and getter services for class <code>DC_RawDataItem</code>.
 * An instance of class <code>DC_RawDataItem</code> is created and the following
 * specific checks are performed:
 * <ol>
 * <li>The value of the variable encapsulated in the raw data item is set and then
 * read back through the data item accessor methods. It is checked that the read-back
 * value is correct. This operation is repeated for all types supported by the
 * <code>DC_RawDataItem</code>.</li>
 * <li>The value of the variable encapsulated by the raw data item is modified
 * using the data item setter methods and the modified value is then read back from
 * the variable itself. This operation is repeated for all types supported by the
 * <code>DC_RawDataItem</code>.</li>
 * </ol>
 * @author Roberto Totaro, Alessandro Pasetti
 * @version 1.0
 */
class TestCaseRawDataItem_1 : public TestCaseGenericSetUp {
public :
	/**
	 * Set the identifier and the name of the test case to, respectively,
	 * ID_RAWDATAITEM*10+1 and "TestCaseRawDataItem_1".
	 */
	TestCaseRawDataItem_1(void);

	/**
	 * Execute the test case. See class comment for details.
	 */
	virtual void runTestCase(void);
};

#endif
