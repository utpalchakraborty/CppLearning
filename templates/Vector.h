#ifndef __VECTOR__H__
#define __VECTOR__H__
#include <stdexcept>
#include <iostream>

namespace Mycode
{
    // since this is a template class, the entire implementation 
    // has to be in a header or a .tcc file that is also included.
    // template definitions cannot be in libraries since this is 
    // a compile time thing. 
    template<typename T>
    class Vector
    {
    private:
	T* elem;
	int sz;

    public:
	// the following allows other templated code
	// to access the type of this template. 
	using value_type = T;

	// normal constructor
	Vector(int s);
	
	// destructor
	~Vector()
	{
	    delete[] elem;
	}

	// index accessing operator.
	T& operator[](int i);

	// a constant index accessing operator
	const T& operator[](int i) const;

	// size - note also the keyword
	// noexcept which says that no exceptions
	// will be thrown by this method.
	int size() const noexcept { return sz; }

	// ...
	// copy and move constructors to be defined.
	Vector(const Vector<T>& t);
	Vector(Vector<T>&& t);

	// copy and move operators to be defined.
	
	
    };

    template<typename T>
    std::ostream& operator<<(std::ostream& ostream, const Vector<T>& v)
    {
	for(int i = 0; i < v.size(); i++)
	{
	    ostream << v[i] << ", ";
	}
	ostream << std::endl;
	return ostream;
    } 

    template<typename T>
    Mycode::Vector<T>::Vector(const Vector<T>& t)
    {
	sz = t.size();
	elem = new T[sz];
	for(int i = 0; i < t.size(); i++)
	{
	    elem[i] = t[i];
	}
    }

    template<typename T>
    T& Mycode::Vector<T>::operator[](int i)
    {
	if(i < 0 || i >= sz)
	{
	    throw std::out_of_range("Vector::operator[]");
	}
	return elem[i];
    }

    template<typename T>
    const T& Mycode::Vector<T>::operator[](int i) const
    {
	if(i < 0 || i >= sz)
	{
	    throw std::out_of_range("Vector::operator[]");
	}
	return elem[i];
    }

    template<typename T>
    Mycode::Vector<T>::Vector(int s)
    {
	if(s <= 0)
	{
	    throw std::length_error("Vector(int s)");
	}
	elem = new T[s];
	sz = s;
    }

    // define a template function. 
    template<typename T>
    void print_vector(const Vector<T>& v)
    {
	for(int i = 0; i < v.size(); i++)
	{
	    std::cout << v[i] << ", ";
	}
	std::cout << std::endl;
    }

    // another type of template is a 
    // functor. A Function template
    template<typename T>
    class LessThan
    {
    private:
	const T t;
    public:
    LessThan(const T& v) : t (v) {}
	
	bool operator()(const T& compareTo)
	{
	    return compareTo < t;
	}
    };

    // here is an example of a function that takes 
    // a template and a functor.
    template<typename T>
	int countLessThan(Vector<T>& v, LessThan<T>& l)
    {
	int count = 0;
	for(int i = 0; i < v.size(); i++)
	{
	    if(l(v[i]))
	    {
		count++;
	    }
	}
	return count;
    }


}
#endif
