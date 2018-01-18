//
// Copyright 2003 P&P Software GmbH (Konstanz, Germany) - All Rights Reserved
//
// PrintHelloWorldAbstractClass.h
//
// Author	A. Pasetti (P&P Software)
//

#ifndef PrintHelloWorldAbstractClassH
#define PrintHelloWorldAbstractClassH


/**
 * Base class that has one abstract method that prints "hello world"
 */
class PrintHelloWorldAbstractClass {

  public:

    /**
     * Empty constructor that returns without doing anything.
     */
    PrintHelloWorldAbstractClass(void);

    /**
     * Print "hello world" and return.
     */
    virtual void printHelloWorld(void) = 0;
};

#endif
