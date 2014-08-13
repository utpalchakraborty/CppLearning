#ifndef __VECTOR__H__
#define __VECTOR__H__

#include <initializer_list>

// class definition in a header file.
// the methods are implemented in a seperate cpp file.
// name of the class

// also note that the class is defined in a new namespace
// this makes sure that the class does not collide with the 
// names of other classes.
namespace My_code {


    class Vector
    {

// private members
    private:
	double* elem;
	int sz;

// public members
    public:

	// constructor. notice the new style element
	// initialization.
	Vector(int s);

	// copy constructor
	Vector(const Vector& v);

	// also copy assignment
	Vector& operator=(const Vector& v);

	// and finally a move constructor
	// && means rvalue reference.
	// a rvalue is something that you cannot assign to
	// like something returned from a function call.
	// this and the move assignment will be chosen
	// over the copy constructor by the compiler
	// when this object is returned from a function 
	// call.
	Vector(Vector&& v);

	// and a move assignment
	Vector& operator=(Vector&& v);
	

	// a constructor with a initializer list.
	// so that the new style initilization is possible
	Vector(std::initializer_list<int> list);

	// an operator definition.
	double& operator[](int i);

	// a simple method definiton.
	// this is defined inline. 
	// so this does not translate to a method call.
	// this method is also marked const. That means
	// that this can be called from other functions 
	// that are marked as const guaranteeing that 
	// no data is being changed.
	int size() const { return sz; }

	// destructor
	~Vector();

    };

// there is also a function defined that does not need to 
// know the internals of the class. 
    void clear_vector(My_code::Vector& v);

    void print_vector(My_code::Vector& v);
}
#endif
