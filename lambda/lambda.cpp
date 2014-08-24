#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <cstdio>
#include <type_traits>

// following is a function defined as a constexpr
// so this is guaranteed to be evaluated at 
// compile time if the input is also a const
// expression.
constexpr int fac(int n)
{
    return (n > 1) ? n * fac(n - 1) : 1;
}

// following is an examople of an attribute.
// there are only two standard defined attributes
// noreturn and carries_dependency
[[noreturn]]
void exit_function()
{
    std::exit(0);
}

// when an array is passed by reference the size of the 
// array is part of the function argument
void af(int(&arg)[4])
{
    // now that is weird syntax.
    // best avoided. 
    // pass a container and enforce the size.
}

// the use of the above is in templates where the number 
// is then deduced

template<typename T, int N>
void tfn(T(&arg)[N])
{
    // now the template code goes here.
    for(int i = 0; i < N; i++)
    {
	std::cout << arg[i] << ",";
    }
    std::cout << std::endl;
}

// default argument declaration.
void fDefault(int i = 0)
{
}

// a function defined with noexcept is 
// guaranteed not to throw an exception
// if it does the program will terminate.
constexpr double compute(double d) noexcept
{
    return d * d;
}

// noexcept can also be defined conditionally.
template<typename T>
constexpr size_t tSquare(T t) noexcept(std::is_pod<T>())
{
    return sizeof(t) * sizeof(t);
} 

// conditional noexcept are important
// the array swap is guranteed not to throw 
// if indivial element swap does not throw.
template<typename T, size_t N>
void swap(T (&a)[N], T (&b)[N]) noexcept(noexcept(swap(*a, *b)));



class A {
    char c;
    char b;
    int a;
};

// any class can be thrown as an exception
// as long as it is copyable.
class MyError{
    int line;
    const char* file;
public:
    MyError(int l, const char* f) : line {l}, file {f} {}

    const int getLine() const { return line; }
    const char* getFile() const { return file; }
};

class CannotBeError
{
public:
    // delete the copy constructor.
    CannotBeError(const CannotBeError& c) = delete;
};


// a function can itself be a try block. 
// this is notational convinience 
// but also provides exception handling 
// facilities in member initializers of 
// constructors.
int main(int argc, char* argv[])
try
{
    A a;
    std::cout << tSquare(a) << std::endl;

    // example of throwing & catching an exception.
    try
    {
	throw MyError { __LINE__, __FILE__ };
    }
    catch(const MyError& e)
    {
	std::cout << "Exception was thrown in file " << e.getFile() << " at line " << e.getLine() << std::endl; 
    }

    // the following line throws a compile error.
    //throw CannotBeError {};

    // following are some predefined macros.

#ifdef __cplusplus
    std::cout << "this is C++" << std::endl;
    std::cout << "Program " << argv[0] << std::endl;
    std::cout << "compiled on " << __DATE__ << " " << __TIME__ << std::endl;
    std::cout << __func__ << " in " << __FILE__ << " at line " << __LINE__ << std::endl;
    std::cout << __STDC_HOSTED__ <<  std::endl;

#endif

    //std::printf("My name is %s %s\n", 2);

    int intArray[] = {1, 2, 3, 4};
    tfn(intArray);

    char charArray[] = { 'a', 'b' };
    tfn(charArray);

    // the simplest possible lambda is the following
    // no captures, no parameters, void return &
    // empty body.
    [] {};

    // this is equivalent to
    []() -> void {};

    std::vector<int>v {32,71,12,45,26,80,53,33};

    // sort the vector with a lambda as a comparator.
    std::sort(v.begin(), v.end(), [](int i, int j) { return (i<j); } );

    // print it out with another lambda
    std::for_each(v.begin(), v.end(), [](int i) { std::cout << i << ",";} );

    // the above lambdas do not do any captures.
    // following one does. and it is passed by reference 
    // so the actual value is changed.
    int total = 0;
    std::for_each(v.begin(), v.end(), [&total](int i) { total += i; });
    std::cout << std::endl << total << std::endl;

    // here the lambda is declared first.
    total = 0;
    auto accum = [&total](int i) { total += i; };
    std::for_each(v.begin(), v.end(), accum);
    std::cout << std::endl << total << std::endl;

    // the lambda can also be casted as a function.
    total = 0;
    std::function<void(int)> faccum = [&total](int i) { total += i; };
    std::for_each(v.begin(), v.end(), faccum);
    std::cout << std::endl << total << std::endl;
    // most of the standard algorithms use lambdas


    try
    {
	throw MyError { __LINE__, __FILE__ };
    }
    catch(const MyError& e)
    {
	std::cout << "Exception was thrown in file " << e.getFile() << " at line " << e.getLine() << std::endl; 
	// here is a rethrow;
	throw; // if the exception is not caught in an outer scope program will terminate.
    }
}
catch(...) // catch all exceotions.
{
	std::cout << "Exception caught in outer scope" << std::endl;
}
