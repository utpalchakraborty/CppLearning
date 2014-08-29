#include <iostream>

//anonymous namespace for this translation unit.
namespace
{
    class X
    {
    private:
	int a;
	int b;
    public:
	// we could just say that everything is default explicitly
	// default constructor
	X() = default;

	// default destructor
	~X() = default;

	// default copy constructor
	X(const X&) = default;

	// default move
	X(X&&) = default;

	// default copy assigment
	X& operator=(const X&) = default;

	// default move assigment
	X& operator=(X&&) = default;

	// all the above are explicitly defined. If nothing was defined then 
	// all would have been implicity defined by the compiler since this is a 
	// simple concrete class.
	
    };

    // outside the class we can define operators

    X& operator+(X a, X b);

    // we can also delete operations.
    class Y
    {
    private:
	int a;
    public:
	// default constructor deleted.
	Y() = delete;
	// deletion is important when we want to suppress unwanted operations
	// like copying. For example copying of unique pointer.

	Y(int i) : a {i} {}
    };

    // another example of delete 
    // since new is deleted this class cannot be allocated on heap.
    // only on stack.
    class Not_on_Free_Store
    {
    public:
	void* operator new(size_t) = delete;
    };
}

int main()
{
    X x {}; // this is fine. Default constructor specified.

    Y y{1}; // this is fine. Call constuctor with int.

    //Y y1 {}; // compile error.

}
