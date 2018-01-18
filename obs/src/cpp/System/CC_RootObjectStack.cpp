

  
//
// Copyright 2003 P&P Software GmbH - All Rights Reserved
//
// CC_RootObjectStack.h
//
// Version	1.0
// Date		30.08.03 (Version 1.0)
// Author	A. Pasetti (P&P Software)
//

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../Base/CC_RootObject.h"
#include "../Base/CC_RootObject.h"
#include "CC_RootObjectStack.h"

CC_RootObjectStack::CC_RootObjectStack() {
    size = 0;
    stackPointer = 0;
    pStack = pNULL;
	setClassId(ID_ROOTOBJECTSTACK);
}

void CC_RootObjectStack::setStackSize(unsigned int size) {
   assert( this->size == 0);      // should not be called more than once
   assert( size > 0);             // stack size must be greater than zero

   pStack = new CC_RootObject*[size];
   assert( pStack!= pNULL );
   this->size = size;
   stackPointer = 0;
}

unsigned int CC_RootObjectStack::getStackSize() const {
   return size;
}

unsigned int CC_RootObjectStack::getNumberOfItems() const {
    return stackPointer;
}


void CC_RootObjectStack::push(CC_RootObject* newItem) {
   assert( (pStack != pNULL) );

   if ( isFull() )
       this->CC_RootObject::getEventRepository()->create(this,EVT_STACK_FULL);
   else {
       pStack[stackPointer]=newItem;
       stackPointer++;
   }
   assert( stackPointer <= size );
}

CC_RootObject* CC_RootObjectStack::pop() {
   assert( (pStack != pNULL) );

   if ( isEmpty() ) {
       this->CC_RootObject::getEventRepository()->create(this,EVT_STACK_EMPTY);
       return pNULL;
   } else {
       stackPointer--;
       return pStack[stackPointer];
   }
}

bool CC_RootObjectStack::isFull() const {
   assert( (pStack != pNULL) );
   return (stackPointer==size);
}

bool CC_RootObjectStack::isEmpty() const {
   assert( (pStack != pNULL) );
   return (stackPointer==0);
}

void CC_RootObjectStack::reset() {
   assert( (pStack != pNULL) );
   stackPointer = 0;
}

bool CC_RootObjectStack::isObjectConfigured() {

   // Check configuration of super object
   if ( !CC_RootObject::isObjectConfigured() )
       return NOT_CONFIGURED;

   if ( (pStack == pNULL) )
       return NOT_CONFIGURED;
   return CONFIGURED;
}

