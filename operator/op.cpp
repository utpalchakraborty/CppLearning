#include <iostream>
#include <stdexcept>

using std::ostream;

namespace
{
    class complex
    {
    private:
	double real;
	double imaginary;

    public:

	// defaults constructor that can be used in many ways
	// also declared as a const expr. That means calculated all 
	// at compile time.
	constexpr complex(double r = 0, double i = 0) : real { r }, imaginary { i } {}

	const double re() const { return real; }

	const double im() const { return imaginary; }

	// we define one operator 
	complex& operator+=(const complex& c)
	    {
		real += c.real;
		imaginary += c.imaginary;
		
		return *this;
	    }

	// finally type conversion.
	// if the imaginary part is 0 then the complex should be 
	// able to converted to double.
	operator double() const
	    {
		if(imaginary != 0)
		{
		    throw std::domain_error {"non-zero imaginary"};
		}
		return real;
	    }

	// the ++ operator is curios because it is a unary prefix 
	// and postfix operator.
	// here is the prefix version
	complex& operator++()
	    {
		real++;
		return *this;
	    }

	// now the postfix version
	// see the unused argument.
	// also note that the old value is returned. 
	// this mimics the traditional usage of say
	// int i++. The value of i is incremented but the value of the 
	// expression is i (the copy of). hence the return of a value 
	// and not the reference.
	complex operator++(int)
	    {
		complex c { real, imaginary };
		real += 1;
		return c;
	    }

	// since ++ is defined we should also define --
	// but the definitions are similar. 
	// these operators are better avoided unless
	// absolutely necessary.


	// similaryly we could define new, new[], delete & delete[]
	// for this class if we desired special allocation 
	// and deallocation behavior. Of course if one of them 
	// is defined it is logical to define all of them.
	void* operator new(size_t);
	void* operator new[](size_t);
	
	void operator delete(void*, size_t);
	void operator delete[](void*, size_t);
	// these are implicitly static members and do not have *this
	// deleting these operations may force some class 
	// not to be allocated on the free store. delete new
		

    };

    // now an operator to print it out to a stream.
    ostream& operator<<(ostream& o, const complex& c)
    {
	o << c.re() << " + i" << c.im();
	return o;
    }

    // using the predefined operator we can now define more.
    complex& operator+(const complex& a, const complex& b)
    {
	complex tmp = a; // default copy constructor is used.
	return tmp.operator+=(b);	
    }

    inline bool operator==(const complex& a, const complex& b)
    {
	return a.re() == b.re() && a.im() == b.im(); 
    }

   //-----------------------------------------
   //               Liteal Operators
   //----------------------------------------
    // always takes long double, or unsigned long long, 
    // or const char *, char, wchar_t 
    constexpr complex operator"" _i(long double d)
    {
	return { static_cast<double>(d), 0 };
    }

    // these can get quite obfuscating. You can have a
    // variadic template literal operator. For example 
    // to define ternary literal
    // 201_t3 (201 in base 3 ).

}


int main()
{
    // define a complex using the constructor
    complex c { 2.3, 3.4 };

    complex a = c + 2.0_i; // using the literal operator

    complex d {3.0, 0};

    c += d;

    std::cout << c << std::endl;

    complex b = c + d + complex { 2.0, 3.5 };

    std::cout << b << std::endl;

    c = 4; // all this works because of implicit conversions 
           // from int to double. if the constructor above is marked 
           // explicit then this will not compile

    c += 5; // this will work because of implicit conversions.

    std::cout << (b == c) << std::endl;

    double myDouble = d; // should work. because d's imaginary is 0;

    c = d + complex { 2.0, 3.5 };


    myDouble = c; // should throw exception.

    std::cout << myDouble << std::endl;
    

}
