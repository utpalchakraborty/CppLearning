#include <iostream>
#include <stdexcept>
#include "Vector.h"

const int j = 10;

// this is a new c++ 11 feature. Constexpr means that 
// this can be evaluated at compile time and will never
// change. This is faster than a const. needs updated
// emacs to understands!!
constexpr int k = j * 10;

// the following expression will silently truncate in old c++
int d = 20.14;

// the auto keyword with the new initializer list.
auto d1 {2};

// but the new initializer will not. the following line will 
// throw a compile error.
// int d3 {20.14};

// since we are going to use this function later we need to define 
// it here. Not like Java...
void range_for_test();
int count_x(char* str, char x);

// we define a structure
struct MyVector1
{
    int size;
    double* elem;
};

void vector_test()
{
    // initia;ize the structure.
    // In this case we also have to do a 
    // memory allocation.
    
    MyVector1 v;
    v.elem = new double[10];
    v.size = 10;

    for(int i = 0; i < 10; i++)
    {
	std::cout << v.elem[i] << std::endl;
    }

    // make sure we delete the allocation 
    // to avoid memory leak.
    delete v.elem;
}

void vector_test2()
{
    try
    {
	My_code::Vector v2(4);
	for(int i = 0 ; i < v2.size(); i++)
	{
	    v2[i] = i * 2;
	}
	My_code::print_vector(v2);
	// clear it out and then print it
	My_code::clear_vector(v2);
	My_code::print_vector(v2);
	// create a vector with a initializer
	My_code::Vector v3 = { 11, 99, 200 };
	My_code::print_vector(v3);

	// now lets test a copy.
	My_code::Vector v4 = v2;
	My_code::print_vector(v4);
	// now test a move
	v4 = std::move(v3);
	My_code::print_vector(v4);
	My_code::print_vector(v3);
	
	
	
	// the following line throws an exception.
	std::cout << v2[10];
    }
    catch(const std::out_of_range& e)
    {
	std::cout << "Exception caught " << e.what() << std::endl;
    }
}

int main()
{
    vector_test2();
    
   vector_test();

  // a simple statement for printing
  std::cout << "Hello World!\n";
  int i = 0;

  // a simple for loop
  // with a switch case inside of it.
  for(; i < 10; i++)
  {
      int mod = i % 2;
      switch(mod)
      {
      case 0:
	  std::cout << "An even line.\n";       
	  break;
      case 1:
	  std::cout << "An odd line.\n";
	  break;
      }
  }

  if(i % 2 == 0)
  {
    std::cout << " the current value of i is even.\n";
  }
  else
  {
    std::cout << " the current value of i is odd.\n";
  }
  std::cout << "End of program.\n";
  
  range_for_test();

  // declaration of double pointer and the use of keyword 
  // nullptr.
  double* doubleptr = nullptr;

  char* str = "The quick brown fox jumps over the lazy dog.";
  std::cout << count_x(str, 'x') << std::endl;

}


// simple pointer arithmentic. 
// a c style string is passed and it counts the number 
// of characters x in the string. 
int count_x(char* str, char x)
{
    if (str == nullptr) return 0;
    int count = 0;
    for(; *str != 0; ++str)
    {
	if(*str == x) count++;
    }
    return count;
}



// the following method shows an array initialization 
// and also the new c++11 range for statement.
void range_for_test()
{
    int v[] = {0,1,2,3,4,5,6,7,8,9,10};

    for(auto x : v)
    {
	std::cout << x;
    }

    // but the above code is slightly inefficient.
    // the variable values of v are copied in x
    // if we just wanted to work with pointers
    for(auto& x : v)
    {
	std::cout << x++;
    }

    // the following line is needed to flush the buffer.
    std::cout << "\n.";

}
