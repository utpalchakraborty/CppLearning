#include <type_traits>
#include <iostream>

// plain old data.
struct A
{    
    int a;
    int b;
    int c;

    // default constructor
    A() = default;
};

// ordering of fields affects sizes.
struct B
{
    char a;
    int b;
    char c;
    
    B()
	{
	    a = 'a';
	    b = 0;
	    c = 'c';
	}
};

// C is smaller because it uses space efficiently.
// layout is smallest to largest.
struct C
{
    char a;
    char b;
    int c;
};

// enum classes. These are strongly typed.
enum class Color
{
    red, green, blue
};


// in this case we are specifying the underlying type
// of the enum. 
enum class Marker : char
{
    one = 1, two = 2, three = 3
};

enum Weak
{
    one, two, three
};

bool enumIsEven(Color c)
{
    return ((static_cast<int>(c) % 2) == 0);
}

int main()
{
    std::cout << "A is a pod? " << std::is_pod<A>() << std::endl;
    // B is not a pod because it does not have default constructor
    std::cout << "B is a pod? " << std::is_pod<B>() << std::endl;
    

    std::cout << "size of B is " << sizeof(B)  << std::endl;
    std::cout << "size of C is " << sizeof(C)  << std::endl;

    std::cout << "Color::red is " << static_cast<int>(Color::red) << std::endl;
    std::cout << "Marker::one is " << static_cast<int>(Marker::one) << std::endl;

    // can convert an int to the classed enum
    Marker marker = static_cast<Marker>(3);
    
    // and vice versa of course.
    std::cout << static_cast<int>(marker) << std::endl;

    // but the following is a compile error.
    //int a = Color::red;

    // since we have a plain enum the members are viewable in this scope
    std::cout << one << std::endl;

    // they also convert to ints
    int val = one;

    // Moral of the story:
    // ALWAYS USE enum class INSTEAD OF enum

    
    // combination of declaration and test.
    // the declared variable is in scope of both the if 
    // and the else block.
    Color color = Color::green;
    if(bool b = enumIsEven(color))
    {
	// b is in scope here. 
	std::cout << "color is even." << std::endl;
    }
    else
    {
	std::cout << "color is not even." << std::endl;
    }

    

}
