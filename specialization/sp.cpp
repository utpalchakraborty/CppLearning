#include <iostream>
#include <functional>

namespace{
    // a template with a type and a value parameter
    // the value is defaulted to 100.
    template<typename T, int N = 100>
    class X{
	T buff[N];
    public:
	void clear(){
	    for(int i = 0; i < N; i++){
		buff[i] = 0; // assumption T c = 0 is valid.
		// copy assignment to 0 of type T is valid.
		// if concepts were there this could be 
		// enforced using a static_assert
	    }
	}

	// size can be determined during compile time.
	constexpr int size() const { return N; }
    };

    // example of more defaults and the template type being used as default.
    // this is a better implementation of X above. 
    template<typename T, int N = 100, T D = T {}>
    class Y{
	T buff[N];
    public:
	void clear(){
	    for(int i = 0; i < N; i++){
		buff[i] = D; 
	    }
	}

	// size can be determined during compile time.
	constexpr int size() const { return N; }

	// as is the default value.
	constexpr T default_value() const { return D; }
    };

    // when we have to use a policy it is better to pass 
    // a functor.
    // so in the above example if the initialization is complicated
    // then we can say
    template<typename T>
    class DefaultT{
    public:
	T operator()() { return T {}; }
    };
    
    // since char 0 does not make sense. Let's specialize this for char
    template<>
    class DefaultT<char> {
    public:
	char operator()() { return '_'; }
    };

    // now it is much nicer. 
    // we have a template that takes a type, a value type 
    // and a template type as parameters. 
    // This is the prototype of the standard templates in the 
    // standard library.
    template<typename T, int N = 100,  typename F = DefaultT<T>>
    class Z{
	T buff[N];
	F f {};
    public:	
	void clear(){
	    for(int i = 0; i < N; i++){
		buff[i] = f(); 
	    }
	}

	// size can be determined during compile time.
	constexpr int size() const { return N; }

	// as is the default value.
	T default_value()  { return f(); }
    };

    // another example.
    template<typename T>
    class List{
    public:
	void which() { std::cout << "generic chosen. " << typeid(T).name() << std::endl; }
    };

    // now specialize for pointer types only. 
    template<typename T>
    class List<T*>{
    public:
	void which() { std::cout << "special chosen. " << typeid(T).name() << std::endl; }
    };

   

}

//here was he was explcitly instantiating the template speciailiation 
// of DefaultT for char. That means at this time the compiler generates the class 
// definition os DefaultT<char>
template class DefaultT<char>;


int main(){
    X<char, 100>  t;
    X<int, 200> t1;
    X<double>  t2;

    t.clear();
    t1.clear();
    t2.clear();

    std::cout << "Size of t2 is " << t2.size() << std::endl;

    Y<char> c;
    std::cout << "Size of c is " << c.size() << std::endl;
    std::cout << "c is defaulted to " << c.default_value() << std::endl;

    Z<int> zd;
    std::cout << "Size of zd is " << zd.size() << std::endl;
    std::cout << "zd is defaulted to " << zd.default_value() << std::endl;

    // in the following example, the defaulted functor is taken 
    // which happens to be the specialized one because we have 
    // specialized the functor for char
    Z<char> zc;
    std::cout << "Size of zc is " << zc.size() << std::endl;
    std::cout << "zc is defaulted to " << zc.default_value() << std::endl;

    // the following would be nice to get working. 
    // Unfortunately, the compiler does not generate a Functor
    // from a lamdba

    /*
    auto l = [](){ return 2; };
    Z<int, 100, decltype(l)> za;
    std::cout << "Size of za is " << za.size() << std::endl;
    std::cout << "za is defaulted to " << za.default_value() << std::endl;
    */


    List<int> x;
    x.which();
    List<X<char>> y;
    y.which();

    List<int*> p;
    p.which();


}
