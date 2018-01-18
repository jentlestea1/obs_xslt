#include "PrintHelloWorldBaseClass.h"
main()
{
//	PrintHelloWorldBaseClass c;
//	c.printHelloWorld();
	PrintHelloWorldBaseClass* c = new PrintHelloWorldBaseClass();
	c->printHelloWorld();
}


