//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseGenericSetUp.h
//
// Version	1.0
// Date		13.09.02
// Author	A. Pasetti (P&P Software)

#ifndef TestCaseGenericSetUpH
#define TestCaseGenericSetUpH

#include "../Utilities/TestCase.h"

/**
 * Base class for generic test cases. This class specializes
 * class <code>TestCase</code> to provide default implementations of
 * the <code>SetUpTestCase</code> and <code>ShutDownTestCase</code>
 * methods that are intended to be suitable for most framework test cases.
 * @author Alessandro Pasetti (P&P Software GmbH)
 * @version 1.0
 * @ingroup TestCases
 */
class TestCaseGenericSetUp : public TestCase {

private :
      static bool firstActivation;

public :

     /**
      * Set the test case name and ID.
      * Calls the constructor of the super class and returns.
      * @param testId the test case ID
      * @param testName the test case name as a string
      */
	   TestCaseGenericSetUp(int testId, char* testName);

     /**
      * Perform basic test initialization actions. More specifically,
      * the following actions are taken: <ul>
      * <li>The system list size is initialized</li>
      * <li>An event repository is created and initialized with a dummy OBS clock</li>
      * <li>A dummy data pool is created as an instance of <code>DC_DummyDataPool</code>
      * and is loaded in <code>CC_RootObject</code> as the system data pool</li>.
      * <li>A dummy parameter database is created as an instance of <code>DC_DummyParameterDatabase</code>
      * and is loaded in <code>CC_RootObject</code> as the system parameter database</li>.
      * <li>The event repository is plugged into the <code>CC_RootObject</code></li>
      * <li>A dummy tracer is created and loaded into the <code>CC_RootObject</code></li>
      * </ul>
      * Note that the above actions initialize the static part of framework components
      * and should therefore be performed only once (the first time the method is called).
      */
	   virtual bool setUpTestCase(void);

     /**
      * Dummy implementation that returns without doing anything.
      * Subclasses should provide concrete test case implementations.
      */
	   virtual void runTestCase(void);

     /**
      * There are no shut-down actions associated to the basic initialization
      * actions performed in method <code>setUpTestCase</code>. Hence, this
      * method only returns "shut down successful" without performing any
      * actions. In order to preserve compatibility with future releases that
      * might be performing some actions in this method, implementations of
      * <code>setUpTestCase</code> in subclasses should call this method before
      * returning as in the following pseudo-code example:
      * <PRE>
      *   ConcreteTestCase::shutDownTestCase() {
      *     bool outcome = . . . ;  // perform class-specific shut-down
      *     if (!outcome)
      *       return outcome;
      *     else
      *       return TestCaseGenericSetUp::shutDownTestCase();
      * </PRE>
      */
	   virtual bool shutDownTestCase(void);
};

#endif
