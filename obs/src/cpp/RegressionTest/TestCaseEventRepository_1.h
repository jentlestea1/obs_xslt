//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseEventRepository_1.h
//
// Version	1.0
// Date		13.09.02
// Author	A. Pasetti (P&P Software)

#ifndef TestCaseEventRepository_1H
#define TestCaseEventRepository_1H

#include "../Utilities/TestCaseGenericSetUp.h"

/**
 * Verify the attribute default values and the object configuration service of class
 * <code>DC_EventRepository</code>.
 * The following specific tests are performed: <ol>
 * <li>The correctness of the class identifier for the <code>DC_EventRepository</code>
 * class is verified</li>
 * <li>A <code>DC_EventRepository</code> instance is created and it is verified
 * that its object configuration service reports "object not configured".</li>
 * <li>The initial (un-configured) values of the event repository attributes are
 * read out and the correctness of their values is verified.</li>
 * <li>A dummy OBS Clock component is loaded and it is verified that <code>getObsClock()</code>
 * returns the correct value.</li>
 * <li>The event repository size is set
 * and it is then verified that the object configuration service correctly reports
 * "object configured".</li>
 * <li>The event repository size attribute is read out and its correctness is
 * verified.</li>
 * </ol>
 * @see DC_EventRepository
 * @author Alessandro Pasetti (P&P Software GmbH)
 * @version 1.0
 */
class TestCaseEventRepository_1 : public TestCaseGenericSetUp {

public :

     /**
      * Set the identifier and the name of the test case to, respectively,
      * ID_EVENTREPOSITORY*10+1 and "TestCaseEventRepository_1".
      */
     TestCaseEventRepository_1(void);

     /**
      * Execute the test case. See class comment for details.
      */
	virtual void runTestCase(void);
};

#endif
