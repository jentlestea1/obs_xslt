//
// Copyright 2003 P&P Software GmbH (Konstanz, Germany) - All Rights Reserved
//
// PrintHelloWorldbaseClass.h
//
// Author	A. Pasetti (P&P Software)
//

#ifndef PrintHelloWorldBaseClassH
#define PrintHelloWorldBaseClassH


/**
 * Base class that has one method that prints "hello world"
 */
class PrintHelloWorldBaseClass {

  public:

    /**
     * Empty constructor that returns without doing anything.
     */
    PrintHelloWorldBaseClass(void);

    /**
     * Print "hello world" and return.
     */
    void printHelloWorld(void);
};

#endif
