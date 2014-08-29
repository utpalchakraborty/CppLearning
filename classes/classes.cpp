#include <iostream>
#include <initializer_list>

using std::string;

// anonymous namespace. That means all that is defined here is only accessible to this translation unit.
namespace
{
    // define a class. This is an example of a concrete class. The entire class and all its members
    // are defined. There are no virtual methods and no inheritance. So it can be stored on the stack
    // and automatically passed by copy etc.
    class Date
    {
    private:
	int d;
	int m;
	int y;
	// the following is mutable. So it can be modified in const functions.
	mutable int z;

	// static to the class. That means only one instance for all instances 
	// of this class.
	static int s;

    public:
	// the constructor is marked explicit so no implicit conversions are not allowed.
	explicit Date(int day = 0, int month = 0, int year = 0) : d {day}, m {month}, y {year}, z {0} {}

	// another constructor with invocation to another constructor
	explicit Date(string day, string month, string year) : Date { std::stoi(day), std::stoi(month), std::stoi(year) } {}

	// the simple modifiers return a reference to this object.
	// so they can be chained.
	Date& addMonth(int n) { m += n; return *this; }

	Date& addDays(int n) { d += n; return *this; }

	int day() const { return d; }
	
	// the following function is const. But still modifies mutable;
	int dayz() const { z++; return d; }

	int zvalue() const { return z; }

	// const does not apply transitively to objects accessed thru pointers.
	// so we could put z in another class and keep a pointer to it. 
	// and access non-const methods using that pointer.
	
	static void sets(int val) { Date::s = val; }

	static void increments() { s++; }

	static int gets() { return s; }

		
    };

    // the static in the class is just the declaration. Here is the actual definition.
    // this provides the linkage.
    int Date::s = 0;

    // on the other hand if a class has even some virtual method 
    // and a destructor because of RAII then it is going to need the full 
    // complement of methods as shown below

    class Time
    {
    private:
	// some data
	
    public:
	Time() {} // constructor (default)

	// constructor with a initializer list. This is not always necessary
	// but often times makes sense if the inherent data structure of the 
	// class is of some sequence of elements.
	Time(std::initializer_list<int> l) {} 

	Time(const Time& t) {} // copy constructor

	Time(Time&& t) {} // move constructor. careful implementation. release this and acquire that.

	Time& operator=(const Time& t) {} // copy operator

	Time& operator=(Time&& t) {} //move operator

	// virtual. because there is a virtual method and this class may be inherited.
	virtual ~Time() {} // destructor

	virtual void someOperation() {}
    };
}

// here is a static variable in a translation unit. This means that this variable will 
// not be exported to the linker and not visible from other translation units. The dual 
// meaning of static.
static int y = 0;

int main()
{
    Date d { 1, 2, 3 }; // this is fine.

    Date d1 {1}; // this is also fine. default values.

    //Date d3 = 15; // this gives compile error.

    d1.addMonth(5).addDays(2);
    d1.dayz();

    std::cout << d1.zvalue() << std::endl;

    Date::sets(10);

    Date::increments();

    std::cout << Date::gets() << std::endl;
    
}
