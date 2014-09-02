#include <iostream>

namespace {
// in this program we define the CRRT pattern
// Curiously Recurring Template Pattern

// First we dfine a base class
    template<typename T>
    class Base {
    public:
	// notice here that a derived function is getting called
	// without even knowning what T is!
	void SomeMethod() {  
	    static_cast<T*>(this)->SomeMethod(); 
	}

	void SomeBaseMethod(){
	    static_cast<T*>(this)->SomeOtherMethod(); 
	}
    };

    template<typename T>
    class Derived : public  Base<Derived<T>> {
    private:
	int val;
    public :
	Derived(int i ) : val{i} {}

	void SomeMethod(){
	    std::cout << "Derived function called. Value :" << val << std::endl;
	}

	void SomeOtherMethod(){
	    std::cout << "Derived Some Other Method called. Value :" << val << std::endl;
	}
    };

    // this can be made as complicated as necessary
    // by passing another template to base.
    // template<typename T, typename U>

    // this can be combined to multiple levels. 
    // where each level is providing some functionality 
    // of the most base class. 

    // using this class hierarchies can be linearized.
    // the interface inheritence can be standard classes
    // while implementation inheritance can be compile time 
    // polymorphism using CRTP.

}


int main(){

    Derived<int> d(1);

    // now here the derived will be called. 
    d.SomeMethod(); // the compiler changes the call to the derived SomeMethod. So this is compile time 
    // overloading.


    // here a method of the base class is called. Which calls the derived class. 
    // the derived call is also optimized by the compiler. 
    d.SomeBaseMethod();

}
