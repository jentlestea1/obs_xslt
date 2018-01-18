//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseBasicDatabase_1.h
//
// Version	1.0
// Date		12.10.02
// Author	A. Pasetti (P&P Software)

#ifndef TestCaseBasicDatabase_1H
#define TestCaseBasicDatabase_1H

#include "../Utilities/TestCaseGenericSetUp.h"

/**
 * Verify the functionalities implemented by the
 * <code>DC_BasicDatabase</code> component.
 * An instance of the component is created and the following
 * specific tests are performed upon it: <ol>
 * <li>It is verified that the class ID of the component has the correct value.</li>
 * <li>It is verified that, after instantiation, the configuration service
 * of the component reports "not configured".</li>
 * <li>The database size is set and then read back and it is checked that the read-back
 * value is correct.</li>
 * <li>The configuration of the database component is completed by loading the default and
 * operational tables and it is verified that the configuration service
 * of the component reports "configured".</li>
 * <li>It is verified that the operational table is initialized to hold a copy
 * of the default table.</li>
 * <li>The setter and getter methods for all parameters types are verified.</li>
 * <li>The pointer getter methods for all parameters types are verified.</li>
 * </ol>
 * @see DC_BasicDatabase
 * @author Alessandro Pasetti (P&P Software GmbH)
 * @version 1.0
 */
class TestCaseBasicDatabase_1 : public TestCaseGenericSetUp {

public :

     /**
      * Set the identifier and the name of the test case to, respectively,
      * ID_BASICDATABASE*10+1 and "TestCaseBasicDatabase_1".
      */
     TestCaseBasicDatabase_1(void);

     /**
      * Execute the test case. See class comment for details.
      */
	virtual void runTestCase(void);
};

#endif
