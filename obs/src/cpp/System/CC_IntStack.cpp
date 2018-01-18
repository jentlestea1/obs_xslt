

  
//
// Copyright 2003 P&P Software GmbH - All Rights Reserved
//
// CC_IntStack.h
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

#include "CC_IntStack.h"

CC_IntStack::CC_IntStack() {
    size = 0;
    stackPointer = 0;
    pStack = pNULL;
	setClassId(ID_INTSTACK);
}

void CC_IntStack::setStackSize(unsigned int size) {
   assert( this->size == 0);      // should not be called more than once
   assert( size > 0);             // stack size must be greater than zero

   pStack = new int[size];
   assert( pStack!= pNULL );
   this->size = size;
   stackPointer = 0;
}

unsigned int CC_IntStack::getStackSize() const {
   return size;
}

unsigned int CC_IntStack::getNumberOfItems() const {
    return stackPointer;
}


void CC_IntStack::push(int newItem) {
   assert( (pStack != pNULL) );

   if ( isFull() )
       this->CC_RootObject::getEventRepository()->create(this,EVT_STACK_FULL);
   else {
       pStack[stackPointer]=newItem;
       stackPointer++;
   }
   assert( stackPointer <= size );
}

int CC_IntStack::pop() {
   assert( (pStack != pNULL) );

   if ( isEmpty() ) {
       this->CC_RootObject::getEventRepository()->create(this,EVT_STACK_EMPTY);
       return pNULL;
   } else {
       stackPointer--;
       return pStack[stackPointer];
   }
}

bool CC_IntStack::isFull() const {
   assert( (pStack != pNULL) );
   return (stackPointer==size);
}

bool CC_IntStack::isEmpty() const {
   assert( (pStack != pNULL) );
   return (stackPointer==0);
}

void CC_IntStack::reset() {
   assert( (pStack != pNULL) );
   stackPointer = 0;
}

bool CC_IntStack::isObjectConfigured() {

   // Check configuration of super object
   if ( !CC_RootObject::isObjectConfigured() )
       return NOT_CONFIGURED;

   if ( (pStack == pNULL) )
       return NOT_CONFIGURED;
   return CONFIGURED;
}

