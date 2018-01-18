

//
// Copyright 2003 P&P Software GmbH - All Rights Reserved
//
// TestCaseIntStack_1.h
//
// Version	1.0
// Date		10.09.03 (Version 1.0)
// Author	A. Pasetti (P&P Software)
//

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../System/CC_IntStack.h"
#include "TestCaseIntStack_1.h"
#include "../Utilities/TestCaseWithEvtCheck.h"

#include <math.h>
#include <float.h>

TestCaseIntStack_1::TestCaseIntStack_1():
	TestCaseWithEvtCheck(ID_INTSTACK*10+1,"TestCaseIntStack_1") {
		return;
}

void TestCaseIntStack_1::runTestCase() {
   CC_IntStack* pStack = new CC_IntStack();
   unsigned int size = 2;
   unsigned int nEvt = getNumberOfEvents();
   int pItem1 = (int)1;
     
   // Check the value of the class identifier
   if ( pStack->getClassId() != ID_INTSTACK )
   {    setTestResult(TEST_FAILURE, "Wrong class identifier");
        return;
   }

   // Check configuration status
   if ( pStack->isObjectConfigured() )
   {    setTestResult(TEST_FAILURE, "Wrong configuration status");
        return;
   }

   // Set the stack size
   pStack->setStackSize(size);
   if ( pStack->getStackSize() != size)
   {    setTestResult(TEST_FAILURE, "Wrong stack size value");
        return;
   }

   // Check configuration status
   if ( !pStack->isObjectConfigured() )
   {    setTestResult(TEST_FAILURE, "Wrong configuration status");
        return;
   }

   // Push one item on stack and check correctness
   pStack->push(pItem1);
   if ( pStack->getNumberOfItems() != 1 )
   {    setTestResult(TEST_FAILURE, "Wrong number of items on stack");
        return;
   }
   
   if ( fabs((float)(pStack->pop()-pItem1))>FLT_EPSILON )
   {    setTestResult(TEST_FAILURE, "Wrong item on stack");
        return;
   } 

   // Check that a pop operation returns pNULL and generates correct event
   if ( pStack->pop() != pNULL )
   {    setTestResult(TEST_FAILURE, "Wrong item on stack");
        return;
   }
   if ( !verifyLatestEvent(nEvt+1,EVT_STACK_EMPTY) )
   {    setTestResult(TEST_FAILURE, "Wrong event");
        return;
   }

   // Perform three push operations and verify event generation
   pStack->push(pItem1);
   pStack->push(pItem1);
   if ( !pStack->isFull() )
   {    setTestResult(TEST_FAILURE, "Stack should be full");
        return;
   }
   pStack->push(pItem1);
   if ( !verifyLatestEvent(nEvt+2,EVT_STACK_FULL) )
   {    setTestResult(TEST_FAILURE, "Wrong event");
        return;
   }

   // Check that there are only two items on the stack
   if ( pStack->getNumberOfItems()!=2 )
   {    setTestResult(TEST_FAILURE, "wrong number of items in stack");
        return;
   }

   // Perform a stack reset and check success
   pStack->reset();
   if ( pStack->getNumberOfItems() != 0 )
   {    setTestResult(TEST_FAILURE, "Reset operation failed");
        return;
   }
   if ( !pStack->isEmpty() )
   {    setTestResult(TEST_FAILURE, "Reset operation failed");
        return;
   }

  setTestResult(TEST_SUCCESS,"Test Successful");
   return;

}
