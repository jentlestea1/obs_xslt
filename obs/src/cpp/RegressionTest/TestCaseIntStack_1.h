

  
//
// Copyright 2003 P&P Software GmbH - All Rights Reserved
//
// TestCaseIntStack_1.h
//
// Version	1.0
// Date		10.10.03 (Version 1.0)
// Author	A. Pasetti (P&P Software)
//

#ifndef TestCaseIntStack_1H
#define TestCaseIntStack_1H

#include "../Utilities/TestCaseWithEvtCheck.h"

/**
 * Check the functionality of the container class for items of type
 * <code>int</code>.
 * One instance of the container class is created and
 * the following specific checks are performed upon it : 
 * The correctness of the class identifier is checked.
 * It is checked that the configuration check service
 * initially reports "not configured".
 * The stack size is set to 2 and it is checked that the set value
 * is correctly reported.
 * It is checked that the configuration check service reports
 * "configured".
 * An item is pushed onto the stack and it is checked that the
 * stack reports "number of items on the stack equals 1".
 * An item is popped from the stack and it is checked that the
 * correct element is returned.
 * A pop operation is performed and it is verified that pNULL
 * is returned and the correct event report is generated.
 * Three items are pushed on the stack and it is verified that
 * only 2 are actually placed on the stack and that the correct event
 * report is generated.
 * It is verified that the stack is full after the second push operation.
 * A reset operation is performed and it is verified that
 * the number of items on the stack is zero and that the stack is
 * empty.
 * 
 * This class was generated automatically by an XSLT program.
 * @see CC_IntStack
 * @author Alessandro Pasetti (P&P Software GmbH)
 * @version 1.0
 */
class TestCaseIntStack_1 : public TestCaseWithEvtCheck {

public :

     /**
      * Set the identifier and the name of the test case to: 
      * ID_INTSTACK*10+1 and "TestCaseIntStack_1".
      */
     TestCaseIntStack_1();

     /**
      * Execute the test case. See class comment for details.
      */
	virtual void runTestCase();
};

#endif

