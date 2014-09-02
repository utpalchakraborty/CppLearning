#include <iostream>
#include <typeinfo>
#include <type_traits>

namespace{
    // here we see how to select the N'th item in a type list
    // in this particular example we can choose one out of four
    // variable number of choices can be represented as variadic
    // templates. (Shown later).
    
    class Nil{};

    // with all defaults we do not select anything.
    template<int I, typename T1 = Nil, typename T2 = Nil, typename T3 = Nil, typename T4 = Nil>
	struct select;

    // now specialize for 0 - 3
    template<typename T1, typename T2, typename T3, typename T4>
    struct select<0, T1, T2, T3, T4> {
	using Type = T1;
    };

    template<typename T1, typename T2, typename T3, typename T4>
    struct select<1, T1, T2, T3, T4> {
	using Type = T2;
    };

    template<typename T1, typename T2, typename T3, typename T4>
    struct select<2, T1, T2, T3, T4> {
	using Type = T3;
    };

    template<typename T1, typename T2, typename T3, typename T4>
    struct select<3, T1, T2, T3, T4> {
	using Type = T4;
    };

    // finally
    template<int I, typename T1, typename T2, typename T3, typename T4>
    using Select = typename select<I, T1, T2, T3, T4>::Type; 
    

    // a usage of this select would be to get the Nth type of a tuple 

    // but we need to make N variable. Following shows how using variadics.
    // once again we start with an empty struct and then specialize it.
    template<unsigned N, typename... Cases>
    struct  selectv;

    // recursive definition of the specialization
    template<unsigned N, typename T, typename... Cases>
    struct selectv<N, T, Cases...> : selectv<N-1, Cases...>{
    };

    // finally end the recursion with N = 0
    template<typename T, typename... Cases>
    struct selectv<0, T, Cases...> {
	using Type = T;
    };

    template<unsigned N, typename... Cases>
    using SelectV = typename selectv<N, Cases...>::Type;


    // for many template declarations we might want to enable 
    // some methods only if some conditions about that type 
    // holds. The following shows how. It is the same basic
    // trick. Define the template and then its specializations
    template<bool C, typename T = void>
    struct my_enable_if {
	using Type = T;
    };

    template<typename T>
    struct my_enable_if<false, T> {};

    template<bool B, typename T = void>
    using MyEnableIf = typename my_enable_if<B, T>::Type;

    // the standard library defined std::enable_if

    struct PodType{
	int a;
	int b;
    };

    struct NonPodType{
	int a;
	int b;
	virtual void f(){}
    };

    template<typename T>
    struct IfTest{

	// usage of our version of enable if. Notice that it can be used only on 
	// Template versions of methods. Because it depends on SFINAE
	template<typename U = T>
	MyEnableIf<std::is_pod<U>::value, void>  somemethod(){
	    std::cout << "This is the Pod Version. " << std::endl;
	}

	template<typename U = T>
	MyEnableIf<!(std::is_pod<U>::value), void>  somemethod(){
	    std::cout << "This is the Non Pod Version. " << std::endl;	    
	}

	// usage of the standard one.
	template<typename U = T>
	std::enable_if<std::is_polymorphic<U>::value, void> methodForPoly(){
	    std::cout << "This is the Poly Version. " << std::endl;
	}
    };

}

int main(){

    Select<2, int, char, double, float> x;
    std::cout << "type of x is " << typeid(x).name() << std::endl;

    typename selectv<4, int, char, double, float, std::string, long>::Type y;
    std::cout << "type of y is " << typeid(y).name() << std::endl;

    // or better still
    SelectV<4, int, char, double, float, std::string, long> y1;
    std::cout << "type of y1 is " << typeid(y1).name() << std::endl;

    std::cout << "PodType is pod? " << !std::is_pod<PodType>::value << std::endl;
    std::cout << "NonPodType is poly? " << std::is_polymorphic<NonPodType>::value << std::endl;

    IfTest<NonPodType> p;
    
    p.somemethod();
    p.methodForPoly();

    // following gives a compile error
    // p.methodForPod();
    

}
