#include <iostream>
#include "numbers.h"

// bring in the entire namespace
using namespace numbers;

extern "C"
{
    void printNumber(int n);
}

// unnamed namespace. used only in this file.
// this namespace/function will not be visible 
// anywhere else.
namespace
{
    void incrementN(int n)
    {
	for(int i = 0; i < n; i++)
	{
	    increment();
	}
    }
}


int main()
{
    std::cout << "Number is now " << getCounter() << std::endl;

    // call this files namespace function.
    incrementN(10);

    std::cout << "Number is now " << counter  << std::endl;
    std::cout << "Number printed using C ";
    printNumber(counter) ;
    std::cout << std::endl;

    
    
}
