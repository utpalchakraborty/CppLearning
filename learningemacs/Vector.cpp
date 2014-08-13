
#include <stdexcept>
#include <iostream>
#include "Vector.h"




// the actual implementations of the vector class
// constructor. notice the new style element
// initialization.
My_code::Vector::Vector(int s) :  sz {s} 
{
    if(sz < 0) throw std::length_error{"My_code::Vector::Vector(int)"};
    elem = new double[sz];
}

My_code::Vector::Vector(std::initializer_list<int> list)
{
    sz = list.size();
    elem = new double[list.size()];
    // initializer list implements the standard iterator.
    std::copy(list.begin(), list.end(), elem);

}

// implementation of copy constructor.
My_code::Vector::Vector(const Vector& v)
{
    sz = v.size();
    elem = new double[v.size()];
    for(int i = 0; i < sz; i++)
    {
	elem[i] = v.elem[i];
    }
}

// implementation of move constructor.
My_code::Vector::Vector(Vector&& v)
{
    if(elem != nullptr)
    {
	delete[] elem;
    }
    sz = v.size();
    elem = v.elem;
    v.sz = 0;
    v.elem = nullptr;
}

// implementation of copy assignment.
My_code::Vector& My_code::Vector::operator=(const Vector& v)
{
    // make sure we free the earlier storage if there is any.
    if(elem != nullptr)
    {
	delete[] elem;
    }
    sz = v.size();
    elem = new double[v.size()];
    for(int i = 0; i < sz; i++)
    {
	elem[i] = v.elem[i];
    }
}

// implementation of move assignment
My_code::Vector& My_code::Vector::operator=(Vector&& v)
{
   // make sure we free the earlier storage if there is any.
    if(elem != nullptr)
    {
	delete[] elem;
    }
    sz = v.size();
    elem = v.elem;
    v.sz = 0;
    v.elem = nullptr;
}


// an operator definition.
double& My_code::Vector::operator[](int i) 
{ 
    // we check that the index is in range. if not throw a 
    // standard exception. Knowing the standard exceptions 
    // are important.
    if(i < 0 || size() <= i)
    {
	throw std::out_of_range{"My_code::Vector::operator[]"};
    }
    return elem[i]; 
}


// destructor
My_code::Vector::~Vector()
{
    if(elem != nullptr)
    {
	delete[] elem;
    }	
}

// the function that was defined earlier in the vector.h file
// that was not part of the class.
void My_code::clear_vector(My_code::Vector& v)
{
    for(int i = 0; i < v.size(); i++)
    {
	v[i] = 0;
    }
}

void My_code::print_vector(My_code::Vector& v)
{
    if(v.size() == 0)
    {
	std::cout << "Empty vector." << std::endl;
    }
    else
    {
	for(int i = 0 ; i < v.size(); i++)
	{
	    std::cout << v[i] << std::endl;
	}
    }
}


