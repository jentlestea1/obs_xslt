#include "PrintHelloWorldDerivedClass.h"
#include "PrintHelloWorldAbstractClass.h"
main()
{
	PrintHelloWorldDerivedClass c;
	c.printHelloWorld();
//	PrintHelloWorldAbstractClass* c = new PrintHelloWorldDerivedClass();
//	c->printHelloWorld();
}


