//
// Copyright 2003 P&P Software GmbH (Konstanz, Germany) - All Rights Reserved
//
// PrintHelloWorldDerivedClass.h
//
// Author	A. Pasetti (P&P Software)
//

#ifndef PrintHelloWorldDerivedClassH
#define PrintHelloWorldDerivedClassH

#include "PrintHelloWorldDerivedClass.h"
#include "PrintHelloWorldAbstractClass.h"


/**
 * Derived class that has one method that prints "hello world"
 */
class PrintHelloWorldDerivedClass : public PrintHelloWorldAbstractClass {

  public:

    /**
     * Empty constructor that returns without doing anything.
     */
    PrintHelloWorldDerivedClass(void);

    /**
     * Print "hello world" and return.
     */
    virtual void printHelloWorld(void);
};

#endif
