#include <iostream>
#include <type_traits> // most of the type functions are defined here.
#include <typeinfo>
#include <list>

namespace {

    struct PodStruct{
	int i;
	int j;
    };

    struct NonPodStruct{
	int i;
	int j;
	virtual void doSomeThing() {}
    };

    //-------------------------------------------------------------------------
    //   Example of choosing a different type depending on some type parameter
    //------------------------------------------------------------------------

    // now some conditional magic.
    // we will define a type as Scoped if it is small 
    // enough to allocate on the stack
    template<typename T>
    struct Scoped {
	// contents  returns the referemce. Only one instance.
	T& operator*() { return x; }
	// pointer dereference returns the address.
	T* operator->() { return &x; }

	Scoped() = default;
	
	// cannot be copied 
	Scoped(const Scoped&) = delete;
	// or assigned to.
	Scoped operator=(const Scoped&) = delete;

    private:
	T x;
    } ;

    // similary a heap object will have the opposite semantics.
    template<typename T>			
    struct Heaped{
	Heaped() : x ( new T ) {} // allocate.
	~Heaped() { delete x; }; // deallocate.

	T& operator*() { return *x; }
	T* operator->() { return x; }
	
	// cannot be copied 
	Heaped(const Heaped&) = delete;
	// or assigned to.
	Heaped operator=(const Heaped&) = delete;

       
	
    private:
	T* x;
    };

    constexpr int on_stack_max = sizeof(std::string);

    // finally define a object Holder. This is the magic.
    template<typename T>
    using HolderType = typename std::conditional<(sizeof(T) <= on_stack_max), // condition comes here.
						 Scoped<T>,
						 Heaped<T>>::type;


    // we can even choose functions at compile time depending on the type.
    struct PodF{
	void operator()(){
	    std::cout << "This is the pod function" << std::endl;
	}
    };

    struct NonPodF{
	void operator()(){
	    std::cout << "This is the non pod function" << std::endl;
	}
    };

    template<typename T>
    using FunctionType = typename std::conditional<(std::is_pod<T>::value),
						   PodF,
						   NonPodF>::type;

    //-----------------------------------------------------------------------
    //    Implementation of conditional using template specialization.
    //----------------------------------------------------------------------

    // we could implement our own conditional. using template magic
    // first define the conditional for true
    template<bool C, typename T, typename F>
    struct MyConditional{
	using type = T;
    };

    // then define a specialization for false.
    template<typename T, typename F>
    struct MyConditional<false, T, F>{
	using type = F;
    };

    // then using my conditional the function type is redefined as follows
    template<typename T>
    using MyFunctionType = typename MyConditional<(std::is_pod<T>::value),
						   PodF,
						   NonPodF>::type;


}

int main() {

    // basic type traits can be looked up like this
    if(std::is_pod<PodStruct>::value){
	std::cout << "Pod Struct is a pod." << std::endl;
    }
    if(!std::is_pod<NonPodStruct>::value){
	std::cout << "No Pod Struct is not a pod." << std::endl;
    }
    // type functions are mostly templates. like above.

    HolderType<PodStruct> t;
    std::cout << "Type of t is " << typeid(t).name() << std::endl;
    HolderType<NonPodStruct> t1;
    std::cout << "Type of t1 is " << typeid(t1).name() << std::endl;

    FunctionType<PodStruct> f;
    f();

    FunctionType<NonPodStruct> g;
    g();

    MyFunctionType<PodStruct> mf;
    mf();

    MyFunctionType<NonPodStruct> mg;
    mg();

    // the standard library used traits heavily. 
    // traits are types associated with a template type
    typename std::list<int>::iterator::value_type it;
    std::cout << "type of it is " << typeid(it).name() << std::endl; //obviously int.
    // but if T is passed into a template then we can use it like the following
    // typename std::list<T>::iterator::value_type 

}
