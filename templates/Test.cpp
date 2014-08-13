#include <iostream>
#include "Vector.h"


// end the recursion by defining one function 
// that takes only one parameter.
template<typename T>
void printVectors(const Mycode::Vector<T>& t)
{
    Mycode::print_vector(t);
}


// variadic templates.
// here a variable number of templated parameters 
// are passed.
template<typename T, typename... Tail>
void printVectors(const Mycode::Vector<T>& t, const Tail&... tail)
{
    Mycode::print_vector(t);
    printVectors(tail...);
}



int main()
{
    Mycode::Vector<int> intVector(2);
    Mycode::Vector<char> charVector(2);
    Mycode::Vector<double> doubleVector(2);
    Mycode::Vector<float> floatVector(2);


    //Mycode::print_vector(intVector);
    std::cout << charVector;

    // calling the variadic.
    //printVectors(intVector, charVector, doubleVector, floatVector);

    Mycode::Vector<int> copy(intVector);
    // printVectors(copy);

    Mycode::LessThan<int>  t(42);

    if(!t(43))
    {
	std::cout << "Obviously 42 is not less than 43." << std::endl;
    }

    std::cout << Mycode::countLessThan(intVector, t) << std::endl;

}
