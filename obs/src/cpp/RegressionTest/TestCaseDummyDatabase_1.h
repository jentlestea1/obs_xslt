//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseDummyDatabase_1.h
//
// Version	1.0
// Date		12.10.02
// Author	A. Pasetti (P&P Software)

#ifndef TestCaseDummyDatabase_1H
#define TestCaseDummyDatabase_1H

#include "../Utilities/TestCaseGenericSetUp.h"

/**
 * Check the functionalities implemented by the
 * <code>DC_DummyDatabase</code> component.
 * An instance of the component is created and the following
 * specific checks are performed upon it: <ol>
 * <li>It is checked that the class ID of the component has the correct value.</li>
 * <li>It is verified that the size of the database has the correct value.</li>
 * <li>It is verified that the single item in the database has the correct value.</li>
 * </ol>
 * @see DC_BasicDatabase
 * @author Alessandro Pasetti (P&P Software GmbH)
 * @version 1.0
 */
class TestCaseDummyDatabase_1 : public TestCaseGenericSetUp {

public :

     /**
      * Set the identifier and the name of the test case to, respectively,
      * ID_DUMMYDATABASE*10+1 and "TestCaseDummyDatabase_1".
      */
     TestCaseDummyDatabase_1(void);

     /**
      * Execute the test case. See class comment for details.
      */
	virtual void runTestCase(void);
};

#endif
